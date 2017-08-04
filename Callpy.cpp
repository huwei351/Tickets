#include <vector>

#include "Callpy.h"
#include "StringUtil.h"

#define PYTHON_PATH "./"
#ifdef DLT
#define PYTHON_MODULE_NAME "dlt"
#else
#define PYTHON_MODULE_NAME "ssq"
#endif

int Callpy::runPythonFunction(std::string func_name, std::string func_args)
{
    long result;
    PyObject *pModule, *pFunc;
    PyObject *pArgs, *pRet;
    // init
    Py_Initialize();

    //ccheck if init fail
    if(!Py_IsInitialized()) {
        return -1;
    }

    // switch path
    swicthPythonPath(PYTHON_PATH);
    // load module
    pModule = loadPythonModule(PYTHON_MODULE_NAME);

    if(!pModule) { // load fail
        printf("[ERROR] Python get module failed.\n");
        return -1;
    }

    // load function
    pFunc = loadPythonFunction(pModule, func_name);

    if(!pFunc || !PyCallable_Check(pFunc)) {
        printf("[ERROR] Can't find funftion (test_add)\n");
        return -1;
    }

    // build args
    pArgs = constructPythonFuctionArgs(func_args);

    if(!pArgs) { // load fail
        printf("[ERROR] Python get args failed.\n");
        return -1;
    }

    // call function
    pRet = PyObject_CallObject(pFunc, pArgs);

    // check if function call success
    if(pRet) {
        result = PyInt_AsLong(pRet);
        //long result = PyLong_AsLong(pRet);
        printf("result: %d\n", result);
    } else {
        printf("[ERROR] Python call function failed.\n");
        return -1;
    }

    Py_Finalize();
    return result;
}

void Callpy::swicthPythonPath(std::string path)
{
    std::string chdir_cmd = std::string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
}

PyObject* Callpy::loadPythonModule(std::string name)
{
    PyObject* moduleName = PyString_FromString(name.c_str());
    //PyObject* moduleName = PyBytes_FromString(name.c_str());
    PyObject* module = PyImport_Import(moduleName);
    return module;
}

PyObject* Callpy::loadPythonFunction(PyObject* module, std::string func_name)
{
    PyObject* func = PyObject_GetAttrString(module, func_name.c_str());
    return func;
}

PyObject* Callpy::constructPythonFuctionArgs(std::string argString)
{
    int arg_num;
    int i = 1;
    PyObject* args;
    std::vector<std::string> lines;

    if(!StringUtil::StringIsEmpty(argString)) {
        StringUtil::StringSplit(lines, argString, "\n");
        arg_num = atoi(lines[0].c_str());
        args = PyTuple_New(arg_num);

        for(i; i < (int)lines.size(); i++) {
            PyObject* arg = PyInt_FromLong(atoi(lines[i].c_str()));
            //PyObject* arg = PyLong_FromLong(atoi(lines[i].c_str()));
            PyTuple_SetItem(args, i - 1, arg);
        }

        if(i - 1 != arg_num) {
            printf("constructPythonFuctionArgs error!\n");
            args = NULL;
        }
    }

    return args;
}
