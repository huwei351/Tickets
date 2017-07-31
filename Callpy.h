#ifndef CALLPY_H
#define CALLPY_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#ifdef WINDOWS
#include <Python.h>
#else
#include <python2.7/Python.h>
#endif


class Callpy
{
    public:
		Callpy() {
		}
		~Callpy() {
		}
        int runPythonFunction(std::string func_name, std::string func_args);
        void swicthPythonPath(std::string path);
        PyObject* loadPythonModule(std::string name);
        PyObject* loadPythonFunction(PyObject* module, std::string func_name);
        PyObject* constructPythonFuctionArgs(std::string argString);
};

#endif
