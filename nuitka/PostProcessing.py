#     Copyright 2021, Kay Hayen, mailto:kay.hayen@gmail.com
#
#     Part of "Nuitka", an optimizing Python compiler that is compatible and
#     integrates with CPython, but also works on its own.
#
#     Licensed under the Apache License, Version 2.0 (the "License");
#     you may not use this file except in compliance with the License.
#     You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#     Unless required by applicable law or agreed to in writing, software
#     distributed under the License is distributed on an "AS IS" BASIS,
#     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#     See the License for the specific language governing permissions and
#     limitations under the License.
#
""" Postprocessing tasks for create binaries or modules.

"""

import ctypes
import os
import sys

from nuitka import Options, OutputDirectories
from nuitka.build.DataComposerInterface import getConstantBlobFilename
from nuitka.PythonVersions import (
    getPythonABI,
    getTargetPythonDLLPath,
    python_version,
    python_version_str,
)
from nuitka.Tracing import postprocessing_logger
from nuitka.utils.FileOperations import (
    getExternalUsePath,
    getFileContents,
    makePath,
    putTextFileContents,
    removeFileExecutablePermission,
)
from nuitka.utils.SharedLibraries import callInstallNameTool
from nuitka.utils.Utils import getOS, isWin32Windows
from nuitka.utils.WindowsResources import (
    RT_GROUP_ICON,
    RT_ICON,
    RT_RCDATA,
    addResourceToFile,
    addVersionInfoResource,
    convertStructureToBytes,
    copyResourcesFromFileToFile,
    getDefaultWindowsExecutableManifest,
    getWindowsExecutableManifest,
)


class IconDirectoryHeader(ctypes.Structure):
    _fields_ = [
        ("reserved", ctypes.c_short),
        ("type", ctypes.c_short),
        ("count", ctypes.c_short),
    ]


class IconDirectoryEntry(ctypes.Structure):
    _fields_ = [
        ("width", ctypes.c_char),
        ("height", ctypes.c_char),
        ("colors", ctypes.c_char),
        ("reserved", ctypes.c_char),
        ("planes", ctypes.c_short),
        ("bit_count", ctypes.c_short),
        ("image_size", ctypes.c_int),
        ("image_offset", ctypes.c_int),
    ]


class IconGroupDirectoryEntry(ctypes.Structure):
    # Make sure the don't have padding issues.
    _pack_ = 2

    _fields_ = (
        ("width", ctypes.c_char),
        ("height", ctypes.c_char),
        ("colors", ctypes.c_char),
        ("reserved", ctypes.c_char),
        ("planes", ctypes.c_short),
        ("bit_count", ctypes.c_short),
        ("image_size", ctypes.c_int),
        ("id", ctypes.c_short),
    )


def readFromFile(readable, c_struct):
    """Read ctypes structures from input."""

    result = c_struct()
    chunk = readable.read(ctypes.sizeof(result))
    ctypes.memmove(ctypes.byref(result), chunk, ctypes.sizeof(result))
    return result


def _addWindowsIconFromIcons(onefile):
    # Relatively detailed handling, pylint: disable=too-many-locals

    icon_group = 1
    image_id = 1
    images = []

    result_filename = OutputDirectories.getResultFullpath(onefile=onefile)

    for icon_spec in Options.getIconPaths():
        if "#" in icon_spec:
            icon_path, icon_index = icon_spec.rsplit("#", 1)
            icon_index = int(icon_index)
        else:
            icon_path = icon_spec
            icon_index = None

        icon_path = os.path.normcase(icon_path)

        if not icon_path.endswith(".ico"):
            postprocessing_logger.info("Not in Windows icon format, converting to it.")

            if icon_index is not None:
                postprocessing_logger.sysexit(
                    "Cannot specify indexes with non-ico format files in '%s'."
                    % icon_spec
                )

            try:
                import imageio
            except ImportError:
                postprocessing_logger.sysexit(
                    "Need to install 'imageio' to automatically convert non-ico icon file in '%s'."
                    % icon_spec
                )

            try:
                image = imageio.imread(icon_path)
            except ValueError:
                postprocessing_logger.sysexit(
                    "Unsupported file format for imageio in '%s', use e.g. PNG files."
                    % icon_spec
                )

            icon_build_path = os.path.join(
                OutputDirectories.getSourceDirectoryPath(onefile=onefile),
                "icons",
            )

            makePath(icon_build_path)

            converted_icon_path = os.path.join(
                icon_build_path,
                "icon-%d.ico" % image_id,
            )

            imageio.imwrite(converted_icon_path, image)
            icon_path = converted_icon_path

        with open(icon_path, "rb") as icon_file:
            # Read header and icon entries.
            header = readFromFile(icon_file, IconDirectoryHeader)
            icons = [
                readFromFile(icon_file, IconDirectoryEntry)
                for _i in range(header.count)
            ]

            if icon_index is not None:
                if icon_index > len(icons):
                    postprocessing_logger.sysexit(
                        "Error, referenced icon index %d in file '%s' with only %d icons."
                        % (icon_index, icon_path, len(icons))
                    )

                icons[:] = icons[icon_index : icon_index + 1]

            postprocessing_logger.info(
                "Adding %d icon(s) from icon file '%s'." % (len(icons), icon_spec)
            )

            # Image data are to be scanned from places specified icon entries
            for icon in icons:
                icon_file.seek(icon.image_offset, 0)
                images.append(icon_file.read(icon.image_size))

        parts = [convertStructureToBytes(header)]

        for icon in icons:
            parts.append(
                convertStructureToBytes(
                    IconGroupDirectoryEntry(
                        width=icon.width,
                        height=icon.height,
                        colors=icon.colors,
                        reserved=icon.reserved,
                        planes=icon.planes,
                        bit_count=icon.bit_count,
                        image_size=icon.image_size,
                        id=image_id,
                    )
                )
            )

            image_id += 1

        addResourceToFile(
            target_filename=result_filename,
            data=b"".join(parts),
            resource_kind=RT_GROUP_ICON,
            lang_id=0,
            res_name=icon_group,
            logger=postprocessing_logger,
        )

    for count, image in enumerate(images, 1):
        addResourceToFile(
            target_filename=result_filename,
            data=image,
            resource_kind=RT_ICON,
            lang_id=0,
            res_name=count,
            logger=postprocessing_logger,
        )


version_resources = {}


def executePostProcessingResources(manifest, onefile):
    """Adding Windows resources to the binary.

    Used for both onefile and not onefile binary, potentially two times.
    """
    result_filename = OutputDirectories.getResultFullpath(onefile=onefile)

    # TODO: Maybe make these different for onefile and not onefile.
    if (
        Options.shallAskForWindowsAdminRights()
        or Options.shallAskForWindowsUIAccessRights()
    ):
        if manifest is None:
            manifest = getDefaultWindowsExecutableManifest()

        if Options.shallAskForWindowsAdminRights():
            manifest.addUacAdmin()

        if Options.shallAskForWindowsUIAccessRights():
            manifest.addUacUiAccess()

    if manifest is not None:
        manifest.addResourceToFile(result_filename, logger=postprocessing_logger)

    if (
        Options.getWindowsVersionInfoStrings()
        or Options.getWindowsProductVersion()
        or Options.getWindowsFileVersion()
    ):
        version_resources.update(
            addVersionInfoResource(
                string_values=Options.getWindowsVersionInfoStrings(),
                product_version=Options.getWindowsProductVersion(),
                file_version=Options.getWindowsFileVersion(),
                file_date=(0, 0),
                is_exe=not Options.shallMakeModule(),
                result_filename=result_filename,
                logger=postprocessing_logger,
            )
        )

    # Attach icons from template file if given.
    template_exe = Options.getWindowsIconExecutablePath()
    if template_exe is not None:
        res_copied = copyResourcesFromFileToFile(
            template_exe,
            target_filename=result_filename,
            resource_kinds=(RT_ICON, RT_GROUP_ICON),
        )

        if res_copied == 0:
            postprocessing_logger.warning(
                "The specified icon template executable %r didn't contain anything to copy."
                % template_exe
            )
        else:
            postprocessing_logger.warning(
                "Copied %d icon resources from %r." % (res_copied, template_exe)
            )
    else:
        _addWindowsIconFromIcons(onefile=onefile)

    splash_screen_filename = Options.getWindowsSplashScreen()
    if splash_screen_filename is not None:
        splash_data = getFileContents(splash_screen_filename, mode="rb")

        addResourceToFile(
            target_filename=result_filename,
            data=splash_data,
            resource_kind=RT_RCDATA,
            lang_id=0,
            res_name=27,
            logger=postprocessing_logger,
        )


def executePostProcessing():
    """Postprocessing of the resulting binary.

    These are in part required steps, not usable after failure.
    """

    result_filename = OutputDirectories.getResultFullpath(onefile=False)

    if not os.path.exists(result_filename):
        postprocessing_logger.sysexit(
            "Error, scons failed to create the expected file %r. " % result_filename
        )

    if isWin32Windows():
        if not Options.shallMakeModule():
            if python_version < 0x300:
                # Copy the Windows manifest from the CPython binary to the created
                # executable, so it finds "MSCRT.DLL". This is needed for Python2
                # only, for Python3 newer MSVC doesn't hide the C runtime.
                manifest = getWindowsExecutableManifest(sys.executable)
            else:
                manifest = None

            executePostProcessingResources(manifest=manifest, onefile=False)

        source_dir = OutputDirectories.getSourceDirectoryPath()

        # Attach the binary blob as a Windows resource.
        addResourceToFile(
            target_filename=result_filename,
            data=getFileContents(getConstantBlobFilename(source_dir), "rb"),
            resource_kind=RT_RCDATA,
            res_name=3,
            lang_id=0,
            logger=postprocessing_logger,
        )

    # On macOS, we update the executable path for searching the "libpython"
    # library.
    if (
        getOS() == "Darwin"
        and not Options.shallMakeModule()
        and not Options.shallUseStaticLibPython()
    ):
        python_abi_version = python_version_str + getPythonABI()
        python_dll_filename = "libpython" + python_abi_version + ".dylib"
        python_lib_path = os.path.join(sys.prefix, "lib")

        # Note: For CPython and potentially others, the rpath for the Python
        # library needs to be set.

        callInstallNameTool(
            filename=result_filename,
            mapping=(
                (
                    python_dll_filename,
                    os.path.join(python_lib_path, python_dll_filename),
                ),
                (
                    "@rpath/Python3.framework/Versions/%s/Python3" % python_version_str,
                    os.path.join(python_lib_path, python_dll_filename),
                ),
            ),
            rpath=python_lib_path,
        )

    # Modules should not be executable, but Scons creates them like it, fix
    # it up here.
    if not isWin32Windows() and Options.shallMakeModule():
        removeFileExecutablePermission(result_filename)

    if isWin32Windows() and Options.shallMakeModule():
        candidate = os.path.join(
            os.path.dirname(result_filename),
            "lib" + os.path.basename(result_filename)[:-4] + ".a",
        )

        if os.path.exists(candidate):
            os.unlink(candidate)

    if isWin32Windows() and Options.shallTreatUninstalledPython():
        dll_directory = getExternalUsePath(os.path.dirname(getTargetPythonDLLPath()))

        cmd_filename = OutputDirectories.getResultRunFilename(onefile=False)

        cmd_contents = """
@echo off
rem This script was created by Nuitka to execute '%(exe_filename)s' with Python DLL being found.
set PATH=%(dll_directory)s;%%PATH%%
"%%~dp0.\\%(exe_filename)s"
""" % {
            "dll_directory": dll_directory,
            "exe_filename": os.path.basename(result_filename),
        }

        putTextFileContents(cmd_filename, cmd_contents)
