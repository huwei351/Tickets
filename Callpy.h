#ifndef CALLPY_H
#define CALLPY_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include <python2.7/Python.h>


class Callpy
{
    public:
        static int runPythonFunction(std::string func_name, std::string func_args);
        static void swicthPythonPath(std::string path);
        static PyObject* loadPythonModule(std::string name);
        static PyObject* loadPythonFunction(PyObject* module, std::string func_name);
        static PyObject* constructPythonFuctionArgs(std::string argString);
};

#endif
