#include "Callpy.h"

#define SSQ_PY_PATH "scrapy_ssq/scrapy_ssq/spiders"
#define SSQ_PY_MODULE_NAME "ssq"

{
    // 初始化Python
    //在使用Python系统前，必须使用Py_Initialize对其
    //进行初始化。它会载入Python的内建模块并添加系统路
    //径到模块搜索路径中。这个函数没有返回值，检查系统
    //是否初始化成功需要使用Py_IsInitialized。
    Py_Initialize();

    // 检查初始化是否成功
    if(!Py_IsInitialized()) {
        return -1;
    }

    // 添加当前路径
    //把输入的字符串作为Python代码直接运行，返回0
    //表示成功，-1表示有错。大多时候错误都是因为字符串
    //中有语法错误。

    // 将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
    string path = SSQ_PY_PATH;
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    // 加载模块
    string name = SSQ_PY_MODULE_NAME;
    PyObject* moduleName = PyString_FromString(name); //模块名，不是文件名
    PyObject* pModule = PyImport_Import(moduleName);

    if(!pModule) { // 加载模块失败
        cout << "[ERROR] Python get module failed." << endl;
        return 0;
    }

    cout << "[INFO] Python get module succeed." << endl;

    // 加载函数
    string func_name = "";
    PyObject* pv = PyObject_GetAttrString(pModule, func_name);

    if(!pv || !PyCallable_Check(pv)) { // 验证是否加载成功
        cout << "[ERROR] Can't find funftion (test_add)" << endl;
        return 0;
    }

    cout << "[INFO] Get function (test_add) succeed." << endl;

    // 设置参数
    //  PyObject* Py_BuildValue(char *format, ...)
    //  把C++的变量转换成一个Python对象。当需要从
    //  C++传递变量到Python时，就会使用这个函数。此函数
    //  有点类似C的printf，但格式不同。常用的格式有
    //  s 表示字符串，
    //  i 表示整型变量，
    //  f 表示浮点数，
    //  O 表示一个Python对象。
    PyObject* args = PyTuple_New(2);   // 2个参数
    PyObject* arg1 = PyInt_FromLong(4);    // 参数一设为4
    PyObject* arg2 = PyInt_FromLong(3);    // 参数二设为3
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);

    // 调用函数
    PyObject* pRet = PyObject_CallObject(pv, args);

    // 获取参数
    if(pRet) { // 验证是否调用成功
        long result = PyInt_AsLong(pRet);
        cout << "result:" << result;
    }

    Py_Finalize();      //释放资源

    return 0;
}
