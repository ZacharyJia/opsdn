#include "controller_support.h"
#include "library.h"

#pragma comment(lib, "opsdn.lib")


int controller_support_send_to_datapath(int conn_id, char* msg, int size)
{
    printf("[opnet] send data from python\n");
    void * msg_buf = op_prg_mem_copy_create(msg, size);
    Ici* ici = op_ici_create("sdn_controller_send_req");
    op_ici_attr_set_int32(ici, "conn_id", conn_id);
    op_ici_attr_set_ptr(ici, "msg_buf", msg_buf);
    op_ici_attr_set_int32(ici, "msg_len", size);

    op_ici_install(ici);
    op_intrpt_schedule_remote(op_sim_time(), 0, op_id_self());
    op_ici_install(OPC_NIL);

    return 0;
}

void controller_support_intrpt_schedule_self(double time, int code) {
    op_intrpt_schedule_self(time, code);
}

double my_op_sim_time() {
    return op_sim_time();
}

void controller_support_init_python_support(Objid modid) {
    OpSdnApi api;
    api.send_to_datapath = controller_support_send_to_datapath;
    api.get_time_time = my_op_sim_time;
    api.intrpt_schedule_self = controller_support_intrpt_schedule_self;

    char python_home_buf[1024];
    op_ima_obj_attr_get_str(modid, "PythonHome", 1024, python_home_buf);
    char script_path_buf[1024];
    op_ima_obj_attr_get_str(modid, "ScriptPath", 1024, script_path_buf);
    char entry_script_buf[128];
    op_ima_obj_attr_get_str(modid, "EntryScript", 128, entry_script_buf);
    char entry_class_buf[128];
    op_ima_obj_attr_get_str(modid, "EntryClass", 128, entry_class_buf);

    OpSdnOptions options;
    options.python_home = python_home_buf;
    options.script_path = script_path_buf;
    options.entry_script = entry_script_buf;
    options.entry_class = entry_class_buf;

    init_op_sdn(api, options);
}

void controller_support_handle_pkt(int conn_id, char* msg, int size) {
    handle_dp_packet(conn_id, msg, size);
}

void controller_support_timer_timeout(int code)
{
    timer_timeout(code);
}
