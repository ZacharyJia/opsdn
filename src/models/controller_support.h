#ifndef CONTROLLER_SUPPORT_H
#define CONTROLLER_SUPPORT_H

#include "opnet.h"

#define INTRPT_CODE_SEND_PKT_TO_SWITCH 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Datapath
{
    int conn_id;
    OpT_Int64 datapathId;
    int ports;
} Datapath;

void controller_support_init_python_support(Objid modid);
int controller_support_send_to_datapath(int conn_id, char* msg, int size);
void controller_support_handle_pkt(int conn_id, char* msg, int size);
void controller_support_timer_timeout(int code);

#ifdef __cplusplus
}
#endif

#endif // CONTROLLER_SUPPORT_H