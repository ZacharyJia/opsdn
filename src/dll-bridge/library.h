#ifndef OPSDN_LIBRARY_H
#define OPSDN_LIBRARY_H

#ifdef OPSDN_LIB
#define OPSDN_EXPORT __declspec(dllexport)
#else
#define OPSDN_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef int(*pFuncSendToDatapath)(int, char*, int);
typedef double(*pFuncSimTime)();
typedef void(*pFuncIntrptScheduleSelf)(double, int);

typedef struct OpSdnApi{
    pFuncSendToDatapath send_to_datapath;
    pFuncSimTime  get_time_time;
    pFuncIntrptScheduleSelf intrpt_schedule_self;
} OpSdnApi;

typedef struct OpSdnOptions {
    char* python_home;
    char* script_path;
    char* entry_script; // entry file name，without '.py'
    char* entry_class; // entry class，this class must be declared in the entry file
} OpSdnOptions;

int _send_to_datapath(int conn_id, char *msg, int size);

double _sim_time();

void _intrpt_schedule_self(double time, int code);

OPSDN_EXPORT void init_op_sdn(OpSdnApi opSdnApi, OpSdnOptions options);

OPSDN_EXPORT void handle_dp_packet(int conn_id, char *msg, int size);

OPSDN_EXPORT void timer_timeout(int code);

#ifdef __cplusplus
}
#endif

#endif //OPSDN_LIBRARY_H
