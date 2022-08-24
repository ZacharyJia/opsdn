#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#include "tv.h"

void sdn_controller_agent_exit_idle() {
#endif


intrpt_type = op_intrpt_type();
intrpt_code = op_intrpt_code();

// printf("Agent State Idle: intrpt type: %d, code: %d\n", intrpt_type, intrpt_code);

// remote interrupt, expected to be from tcp module
if (intrpt_type == OPC_INTRPT_REMOTE)
{
    iciptr = op_intrpt_ici();
    op_ici_format(iciptr, ici_name);
    // printf("ici format is %s\n", ici_name);
    if (strcmp(ici_name, "tcp_status_ind") == 0) {
        int conn_id;
        int status;
        // op_ici_print(iciptr);
        op_ici_attr_get_int32(iciptr, "conn_id", &conn_id);
        op_ici_attr_get_int32(iciptr, "status", &status);

        if (status == TCPC_IND_ESTAB || status == TCPC_IND_SEG_FWD) {
            // if tcp tell us the connection is established or a segment will be forwarded,
            // we reply them we are ready to received packet now.
            tcp_receive_command_send(tcp_app_handle_map[conn_id], 1);
        }
    } else if (strcmp(ici_name, "tcp_open_ind") == 0) {
        // When a tcp client connected to us, the original app handle will be occupied and we need start a new listen.
        // But we cannot call it here because we are in the improper environment. So we make a self interrupt to notify us to listen.
        op_intrpt_schedule_self(op_sim_time(), INTRPT_CODE_CREATE_NEW_CONN);
    } else if(strcmp(ici_name, "sdn_controller_send_req") == 0) {
        // we will deserialize the openflow packet from the controller and send them to tcp module.
        int conn_id;
        char* msg_buf;
        int msg_len;
        op_ici_attr_get_int32(iciptr, "conn_id", &conn_id);
        op_ici_attr_get_ptr(iciptr, "msg_buf", (void**)&msg_buf);
        op_ici_attr_get_int32(iciptr, "msg_len", &msg_len);

        OpT_Packet_Size converted = 0;
        Packet* pkptr = openflow_tcp_sar_deserialization_callback(msg_buf, msg_len, &converted);
        if (pkptr)
        {
            tcp_data_send(tcp_app_handle_map[conn_id], pkptr);
        }
    }
}
else if (intrpt_type == OPC_INTRPT_STRM)
{
    pkptr = op_get_pk(op_intrpt_strm());
    // op_pk_print(pkptr);
    iciptr = op_intrpt_ici();
    // op_ici_print(iciptr);
    int conn_id;
    int status;

    op_ici_attr_get_int32(iciptr, "conn_id", &conn_id);
    op_ici_attr_get_int32(iciptr, "status", &status);

    if (status == TCPC_IND_SEG_FWD) {
        tcp_receive_command_send(tcp_app_handle_map[conn_id], 1);
    }

    if (op_pk_is_format(pkptr, "openflow_msg")) {
        int msg_type;
        op_pk_nfd_get_int32(pkptr, "type", &msg_type);
        printf("openflow_msg type: %d\n", msg_type);
        handle_openflow_packet(conn_id, pkptr);
    }
}
else if (intrpt_type == OPC_INTRPT_SELF && intrpt_code == INTRPT_CODE_CREATE_NEW_CONN)
{
    create_listen_connection();
}
else if (intrpt_type == OPC_INTRPT_SELF && intrpt_code >= INTRPT_CODE_PYTHON_TIMER_MIN && intrpt_code <= INTRPT_CODE_PYTHON_TIMER_MAX)
{
    controller_support_timer_timeout(intrpt_code);
}



#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
}
#endif
