#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#include "tv.h"

void sdn_controller_agent_enter_init() {
#endif

sitl_log_handle = op_prg_log_handle_create(OpC_Log_Category_Lowlevel, "SITL", "Packet Translation", 1024);
sitl_packet_translation_init_internal();
op_pk_sitl_packet_translation_init();

controller_support_init_python_support(op_id_self());


my_node_objid = op_id_parent(op_id_self());
printf("My node objid is %d\n", my_node_objid);

tcp_app_handle = tcp_app_register(op_id_self());

List* packetList = prg_list_create();
char tcp_mod_id_str[32];
sprintf(tcp_mod_id_str, "%d", op_id_self());
oms_data_def_entry_insert("OpenFlow Manager Packet List", tcp_mod_id_str, (void*)packetList);

op_intrpt_schedule_self(op_sim_time()+0.1, 0);

// 让创建新连接的自中断的优先级更高，保证能够接收到后续其他的数据
op_intrpt_priority_set(OPC_INTRPT_SELF, INTRPT_CODE_CREATE_NEW_CONN, 100);

#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
}
#endif
