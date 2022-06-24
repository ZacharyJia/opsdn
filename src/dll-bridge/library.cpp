#include "library.h"

#include <iostream>
#include "Python.h"
#include "opsdn.h"
#include "Windows.h"

#define SCRIPT_BUF_LEN 2048

static OpSdnApi api;
static PyObject* pHandleMethod;
static PyObject* pTimerTimeoutMethod;

int _send_to_datapath(int conn_id, char *msg, int size)
{
//    std::cout << ("send data from python!\n");
//    std::cout << conn_id << " " << msg << " " << size << std::endl;
    return api.send_to_datapath(conn_id, msg, size);
}

double _sim_time()
{
    return api.get_time_time();
}

void _intrpt_schedule_self(double time, int code)
{
    api.intrpt_schedule_self(time, code);
}

//char*转wchar_t*
wchar_t* AnsiToUnicode(const char* szStr)
{
    int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
    if (nLen == 0)
    {
        return nullptr;
    }
    wchar_t* pResult = new wchar_t[nLen];
    MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
    return pResult;
}

//wchar_t*ת转char*
char* UnicodeToAnsi(const wchar_t* szStr)
{
    int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );
    if (nLen == 0)
    {
        return nullptr;
    }
    char* pResult = new char[nLen];
    WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );
    return pResult;
}

void replace_path_slash(char* path)
{
    int len = strlen(path);
    for (int i = 0; i < len; i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
}


void init_op_sdn(OpSdnApi opSdnApi, OpSdnOptions options)
{
    printf("init_op_sdn called\n");
    auto res = Py_IsInitialized();
    printf("Py_IsInitialized: %d\n", res);

    api = opSdnApi;
    wchar_t* python_home_wchar = AnsiToUnicode(options.python_home);
    std::wcout << python_home_wchar << std::endl;
    if (python_home_wchar == nullptr) {
        std::cout << "python home is invalid!" << std::endl;
        return;
    }
    Py_SetPythonHome(python_home_wchar);
    delete python_home_wchar;

    char* path = new char[strlen(options.python_home) + 8];
    strcpy(path, options.python_home);
    strcat(path, "\\Lib");
    wchar_t* python_path_wchar = AnsiToUnicode(path);
    Py_SetPath(python_path_wchar);
    delete python_path_wchar;

    PyImport_AppendInittab("opsdn", &PyInit_opsdn);
    Py_Initialize();

    PyRun_SimpleString("import sys");
    char script_buf[SCRIPT_BUF_LEN];
    int cnt = snprintf(script_buf, SCRIPT_BUF_LEN, "sys.path.append('%s')", options.script_path);
    if (cnt > SCRIPT_BUF_LEN) {
        std::cout << "path is too long for SCRIPT_BUF_LEN, please use larger SCRIPT_BUF_LEN!" << std::endl;
        return;
    }
    replace_path_slash(script_buf);
    std::cout << script_buf << std::endl;
    PyRun_SimpleString(script_buf);

    cnt = snprintf(script_buf, SCRIPT_BUF_LEN, "sys.path.append('%s\\Lib\\site-packages')", options.python_home);
    if (cnt > SCRIPT_BUF_LEN) {
        std::cout << "path is too long for SCRIPT_BUF_LEN, please use larger SCRIPT_BUF_LEN!" << std::endl;
        return;
    }
    replace_path_slash(script_buf);
    std::cout << script_buf << std::endl;
    PyRun_SimpleString(script_buf);

    cnt = snprintf(script_buf, SCRIPT_BUF_LEN, "sys.path.append('%s\\DLLs')", options.python_home);
    if (cnt > SCRIPT_BUF_LEN) {
        std::cout << "path is too long for SCRIPT_BUF_LEN, please use larger SCRIPT_BUF_LEN!" << std::endl;
        return;
    }
    replace_path_slash(script_buf);
    std::cout << script_buf << std::endl;
    PyRun_SimpleString(script_buf);

    auto pmod = PyImport_ImportModule(options.entry_script);
    PyErr_Print();
    std::cout << "pmod: " << pmod << std::endl;

    auto pclass = PyObject_GetAttrString(pmod, options.entry_class);
    std::cout << "pclass: " << pclass << std::endl;
    Py_DecRef(pmod);

    auto pargs = Py_BuildValue("()");
    auto pinstance = PyEval_CallObject(pclass, pargs);
    std::cout << "pinstance: " << pinstance << std::endl;
    Py_DecRef(pclass);
    Py_DecRef(pargs);

    pHandleMethod = PyObject_GetAttrString(pinstance, "handle_dp_pkt");
    std::cout << "pHandleMethod: " << pHandleMethod << std::endl;
    Py_DecRef(pinstance);

    pmod = PyImport_ImportModule("opsdnpy.op_timer");
    PyErr_Print();
    std::cout << "ptimer_mod: " << pmod << std::endl;

    auto pTimerClass = PyObject_GetAttrString(pmod, "OpTimer");
    PyErr_Print();
    std::cout << "pTimerClass: " << pTimerClass << std::endl;
    Py_DecRef(pmod);

    pargs = Py_BuildValue("()");
    auto pTimerInstance = PyEval_CallObject(pTimerClass, pargs);
    PyErr_Print();
    std::cout << "pTimerInstance: " << pTimerInstance << std::endl;
    Py_DecRef(pTimerClass);
    Py_DecRef(pargs);

    pTimerTimeoutMethod = PyObject_GetAttrString(pTimerInstance, "timer_timeout");
    std::cout << "pTimerTimeoutMethod: " << pTimerTimeoutMethod << std::endl;

    Py_DecRef(pTimerInstance);
}


void handle_dp_packet(int conn_id, char *msg, int size)
{
    std::cout << ("handle packet from opnet!\n");
    std::cout << "conn_id:" << conn_id << " " << "size: " << size << std::endl;
//    for (int i = 0; i < size; i++) {
//        std::cout << msg[i];
//    }
//    std::cout << std::endl;
    PyRun_SimpleString("print('Hello from Python!!!')\n");
//    PyRun_SimpleString("import sys\nprint(sys.version)\n");
//    PyRun_SimpleString("import opsdn\n");

    auto pargs = Py_BuildValue("(iy#i)", conn_id, msg, size, size);
    auto pres = PyEval_CallObject(pHandleMethod, pargs);
    PyErr_Print();
    char* cstr;
    PyArg_Parse(pres, "s", &cstr);
    std::cout << "call pHandleMethod, result: " << cstr << std::endl;

//    PyRun_SimpleString("opsdn.send_to_dp(123, bytearray(b'aaabbb'), 10)\n");
    // Py_Finalize();
}

void timer_timeout(int code)
{
    auto pargs = Py_BuildValue("(i)", code);
    auto pres = PyEval_CallObject(pTimerTimeoutMethod, pargs);
    PyErr_Print();
    char* cstr;
    PyArg_Parse(pres, "s", &cstr);
    std::cout << "call pHandleMethod, result: " << cstr << std::endl;
}
