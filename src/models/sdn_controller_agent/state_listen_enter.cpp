#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#include "tv.h"

void sdn_controller_agent_enter_listen() {
#endif


create_listen_connection();

op_intrpt_schedule_self(op_sim_time(), 0);

#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
}
#endif
