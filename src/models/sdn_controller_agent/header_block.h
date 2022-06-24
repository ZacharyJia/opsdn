#include "tpal_api.h"
#include "tcp_api_v3.h"
#include "openflow_support.h"
#include "map"
#include "controller_support.h"
#include "sitl_packet_translation.h"


void create_listen_connection();

void handle_openflow_packet(int conn_id, Packet* pkptr);

extern "C" Log_Handle sitl_log_handle;
extern void sitl_packet_translation_init_internal(void);

#define INTRPT_CODE_CREATE_NEW_CONN 2

#define INTRPT_CODE_PYTHON_TIMER_MIN 1000
#define INTRPT_CODE_PYTHON_TIMER_MAX 10000