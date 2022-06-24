from libc.stdlib cimport malloc
from libc.string cimport strcpy, strlen


cdef extern from 'library.h':
    ctypedef struct Datapath:
        pass
    int _send_to_datapath(int, char* msg, int size)
    double _sim_time()
    void _intrpt_schedule_self(double, int)


def send_to_dp(conn_id, bytearray msg, size):
    cdef char* msg_c_string = msg
    _send_to_datapath(conn_id, msg_c_string, size)

def sim_time():
    return _sim_time()

def intrpt_schedule_self(time, code):
    _intrpt_schedule_self(time, code)

cdef public sayHi():
    pass

# cdef public send():
#     a = 'aaa'
#     cdef char * pkt_fmt = "hihihi"
#     c_string_ptr = <char *> malloc((6 + 1) * sizeof(char))
#     strcpy(c_string_ptr, a)
#     op_pk_create(pkt_fmt)