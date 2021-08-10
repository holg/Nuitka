//     Copyright 2021, Kay Hayen, mailto:kay.hayen@gmail.com
//
//     Part of "Nuitka", an optimizing Python compiler that is compatible and
//     integrates with CPython, but also works on its own.
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
/* WARNING, this code is GENERATED. Modify the template CodeTemplateCallsPositional.j2 instead! */

/* This file is included from another C file, help IDEs to still parse it on its own. */
#ifdef __IDE_ONLY__
#include "nuitka/prelude.h"
#endif

PyObject *CALL_FUNCTION_NO_ARGS(PyObject *called) {
    CHECK_OBJECT(called);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 0 == function->m_args_positional_count) {
            result = function->m_c_code(function, NULL);
        } else if (function->m_args_simple && 0 + function->m_defaults_given == function->m_args_positional_count) {
            PyObject **python_pars = &PyTuple_GET_ITEM(function->m_defaults, 0);

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsEmpty(function, python_pars))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 0 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[0 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       0 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1 + 0, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionNoArgs(function, method->m_object);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (likely(flags & METH_NOARGS)) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result = (*method)(self, NULL);

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (0 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = const_tuple_empty;
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = const_tuple_empty;
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, NULL, 0, NULL);
#else
                PyObject *pos_args = const_tuple_empty;
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 0);
#endif
            } else {
                PyObject *pos_args = const_tuple_empty;
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return _fast_function_noargs(called);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, const_tuple_empty, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_SINGLE_ARG(PyObject *called, PyObject *arg) {
    PyObject **args = &arg; // For easier code compatibility.
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 1);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 1 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 1; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 1 * sizeof(PyObject *));
            memcpy(python_pars + 1, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 1))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 1 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[1 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 1; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       1 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 1 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 1, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 1)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (1 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if ((flags & METH_O)) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result = (*method)(self, args[0]);

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 1);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 1);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 1, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 1);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 1);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 1);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 1);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 1);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS1(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 1);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 1 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 1; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 1 * sizeof(PyObject *));
            memcpy(python_pars + 1, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 1))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 1 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[1 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 1; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       1 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 1 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 1, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 1)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (1 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if ((flags & METH_O)) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result = (*method)(self, args[0]);

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 1, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 1);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 1);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS2(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 2);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 2 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 2; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 2 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 2 * sizeof(PyObject *));
            memcpy(python_pars + 2, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 2))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 2 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[2 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 2; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       2 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 2 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 2, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 2)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (2 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (2 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 2);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 2);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 2, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 2);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 2);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 2);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 2);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 2);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS2(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 2);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 2 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 2; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 2 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 2 * sizeof(PyObject *));
            memcpy(python_pars + 2, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 2))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 2 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[2 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 2; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       2 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 2 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 2, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 2)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (2 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (2 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 2, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 2);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 2);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS3(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 3);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 3 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 3; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 3 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 3 * sizeof(PyObject *));
            memcpy(python_pars + 3, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 3))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 3 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[3 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 3; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       3 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 3 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 3, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 3)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (3 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (3 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 3);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 3);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 3, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 3);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 3);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 3);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 3);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 3);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS3(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 3);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 3 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 3; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 3 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 3 * sizeof(PyObject *));
            memcpy(python_pars + 3, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 3))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 3 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[3 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 3; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       3 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 3 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 3, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 3)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (3 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (3 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 3, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 3);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 3);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS4(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 4);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 4 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 4; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 4 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 4 * sizeof(PyObject *));
            memcpy(python_pars + 4, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 4))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 4 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[4 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 4; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       4 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 4 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 4, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 4)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (4 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (4 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 4);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 4);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 4, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 4);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 4);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 4);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 4);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 4);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS4(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 4);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 4 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 4; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 4 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 4 * sizeof(PyObject *));
            memcpy(python_pars + 4, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 4))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 4 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[4 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 4; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       4 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 4 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 4, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 4)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (4 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (4 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 4, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 4);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 4);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS5(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 5);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 5 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 5; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 5 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 5 * sizeof(PyObject *));
            memcpy(python_pars + 5, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 5))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 5 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[5 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 5; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       5 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 5 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 5, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 5)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (5 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (5 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 5);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 5);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 5, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 5);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 5);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 5);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 5);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 5);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS5(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 5);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 5 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 5; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 5 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 5 * sizeof(PyObject *));
            memcpy(python_pars + 5, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 5))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 5 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[5 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 5; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       5 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 5 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 5, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 5)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (5 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (5 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 5, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 5);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 5);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS6(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 6);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 6 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 6; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 6 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 6 * sizeof(PyObject *));
            memcpy(python_pars + 6, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 6))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 6 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[6 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 6; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       6 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 6 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 6, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 6)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (6 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (6 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 6);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 6);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 6, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 6);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 6);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 6);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 6);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 6);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS6(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 6);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 6 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 6; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 6 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 6 * sizeof(PyObject *));
            memcpy(python_pars + 6, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 6))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 6 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[6 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 6; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       6 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 6 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 6, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 6)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (6 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (6 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 6, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 6);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 6);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS7(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 7);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 7 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 7; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 7 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 7 * sizeof(PyObject *));
            memcpy(python_pars + 7, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 7))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 7 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[7 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 7; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       7 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 7 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 7, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 7)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (7 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (7 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 7);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 7);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 7, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 7);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 7);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 7);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 7);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 7);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS7(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 7);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 7 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 7; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 7 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 7 * sizeof(PyObject *));
            memcpy(python_pars + 7, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 7))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 7 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[7 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 7; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       7 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 7 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 7, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 7)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (7 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (7 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 7, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 7);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 7);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS8(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 8);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 8 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 8; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 8 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 8 * sizeof(PyObject *));
            memcpy(python_pars + 8, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 8))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 8 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[8 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 8; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       8 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 8 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 8, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 8)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (8 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (8 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 8);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 8);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 8, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 8);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 8);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 8);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 8);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 8);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS8(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 8);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 8 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 8; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 8 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 8 * sizeof(PyObject *));
            memcpy(python_pars + 8, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 8))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 8 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[8 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 8; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       8 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 8 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 8, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 8)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (8 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (8 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 8, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 8);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 8);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS9(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 9);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 9 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 9; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 9 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 9 * sizeof(PyObject *));
            memcpy(python_pars + 9, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 9))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 9 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[9 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 9; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       9 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 9 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 9, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 9)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (9 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (9 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 9);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 9);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 9, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 9);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 9);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 9);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 9);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 9);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS9(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 9);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 9 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 9; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 9 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 9 * sizeof(PyObject *));
            memcpy(python_pars + 9, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 9))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 9 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[9 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 9; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       9 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 9 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 9, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 9)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (9 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (9 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 9, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 9);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 9);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS10(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 10);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 10 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 10; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 10 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 10 * sizeof(PyObject *));
            memcpy(python_pars + 10, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 10))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 10 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[10 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 10; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       10 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 10 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 10, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 10)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (10 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (10 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 10);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                PyObject *pos_args = MAKE_TUPLE(args, 10);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
                Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 10, NULL);
#else
                PyObject *pos_args = MAKE_TUPLE(args, 10);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 10);
                Py_DECREF(pos_args);
#endif
            } else {
                PyObject *pos_args = MAKE_TUPLE(args, 10);
                result = (*method)(self, pos_args);
                Py_DECREF(pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 10);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 10);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_POSARGS10(PyObject *called, PyObject *pos_args) {
    assert(PyTuple_CheckExact(pos_args));
    PyObject **args = &PyTuple_GET_ITEM(pos_args, 0);
    CHECK_OBJECT(called);
    CHECK_OBJECTS(args, 10);

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 10 == function->m_args_positional_count) {
            for (Py_ssize_t i = 0; i < 10; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 10 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 10 * sizeof(PyObject *));
            memcpy(python_pars + 10, &PyTuple_GET_ITEM(function->m_defaults, 0),
                   function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (unlikely(parseArgumentsPos(function, python_pars, args, 10))) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 10 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[10 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 10; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple &&
                       10 + 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars + 1, args, 10 * sizeof(PyObject *));
                memcpy(python_pars + 1 + 10, &PyTuple_GET_ITEM(function->m_defaults, 0),
                       function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 10)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes no arguments (10 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError, "%s() takes exactly one argument (10 given)",
                                                ((PyCFunctionObject *)called)->m_ml->ml_name);
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

#else
            if (flags == (METH_VARARGS | METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, args, 10, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 10);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_SystemError, "NULL result without error in PyObject_Call");
                }

                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(called, args, 10);
    }

#if 0
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    return result;
}
/* WARNING, this code is GENERATED. Modify the template CodeTemplateCallsMethodPositional.j2 instead! */

/* This file is included from another C file, help IDEs to still parse it on its own. */
#ifdef __IDE_ONLY__
#include "nuitka/prelude.h"
#endif

PyObject *CALL_METHOD_NO_ARGS(PyObject *source, PyObject *attr_name) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result = Nuitka_CallMethodFunctionNoArgs((struct Nuitka_FunctionObject const *)descr, source);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_NO_ARGS(descr);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_NO_ARGS(called_object);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionNoArgs((struct Nuitka_FunctionObject const *)called_object, source);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_NO_ARGS(method);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_NO_ARGS(called_object);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_NO_ARGS(called_object);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_SINGLE_ARG(PyObject *source, PyObject *attr_name, PyObject *arg) {
    PyObject **args = &arg; // For easier code compatibility.
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 1);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 1);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(descr, args[0]);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 1);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(method, args[0]);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_SINGLE_ARG(called_object, args[0]);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS2(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 2);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 2);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS2(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS2(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 2);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS2(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS2(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS3(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 3);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 3);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS3(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS3(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 3);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS3(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS3(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS3(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS4(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 4);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 4);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS4(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS4(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 4);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS4(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS4(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS4(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS5(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 5);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 5);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS5(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS5(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 5);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS5(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS5(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS6(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 6);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 6);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS6(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS6(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 6);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS6(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS6(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS6(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS7(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 7);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 7);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS7(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS7(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 7);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS7(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS7(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS7(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS8(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 8);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 8);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS8(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS8(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 8);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS8(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS8(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS8(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS9(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 9);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 9);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS9(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS9(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 9);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS9(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS9(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS9(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
PyObject *CALL_METHOD_WITH_ARGS10(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    CHECK_OBJECTS(args, 10);

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL) {
            Py_INCREF(descr);

            if (NuitkaType_HasFeatureClass(Py_TYPE(descr))) {
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr)) {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
                    Py_DECREF(called_object);
                    return result;
                }
            }
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if (dictoffset != 0) {
            // Negative dictionary offsets have special meaning.
            if (dictoffset < 0) {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0) {
                    tsize = -tsize;
                }
                size = _PyObject_VAR_SIZE(type, tsize);

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **)((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL) {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = DICT_GET_ITEM1(dict, attr_name);

            if (called_object != NULL) {
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result =
                    Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)descr, source, args, 10);
                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
                Py_DECREF(called_object);
                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS10(descr, args);
            Py_DECREF(descr);
            return result;
        }

#if PYTHON_VERSION < 0x300
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            PyString_AS_STRING(attr_name));
#else
        PyErr_Format(PyExc_AttributeError, "'%s' object has no attribute '%U'", type->tp_name, attr_name);
#endif
        return NULL;
    }
#if PYTHON_VERSION < 0x300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object =
            GET_STRING_DICT_VALUE((PyDictObject *)source_instance->in_dict, (PyStringObject *)attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS10(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(source_instance->in_class, attr_name);

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)called_object, source,
                                                        args, 10);
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(called_object, source, (PyObject *)source_instance->in_class);

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS10(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS10(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "%s instance has no attribute '%s'",
                                                PyString_AS_STRING(source_instance->in_class->cl_name),
                                                PyString_AS_STRING(attr_name));

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {source, attr_name};

            called_object = CALL_FUNCTION_WITH_ARGS2(source_instance->in_class->cl_getattr, args2);

            if (unlikely(called_object == NULL)) {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(source, attr_name);

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(source, (char *)Nuitka_String_AsString_Unchecked(attr_name));

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS10(called_object, args);
        Py_DECREF(called_object);
        return result;
    } else {
        SET_CURRENT_EXCEPTION_TYPE0_FORMAT2(PyExc_AttributeError, "'%s' object has no attribute '%s'", type->tp_name,
                                            Nuitka_String_AsString_Unchecked(attr_name));

        return NULL;
    }
}
