# OPSDNPY APIs

### `opsdn` Module

#### sim_time() -> double
Get current simulation time, equivalent to `op_sim_time()` in OPNET.

#### send_to_dp(conn_id, msg, size)
Send serialized packet to the SDN switch. This is a low-level API and is not recommended to use. Users are expected to use datapath.send_msg to send packets instead.

* conn_id: tcp connection id
* msg: serialized packet
* size: packet length


#### intrpt_schedule_self(time, code)
Set a self interrupt, equivalent to `op_intrpt_schedule_self` in OPNET.
This is a low-level API and is not recommended to use. Users are expected to use `OpTimer` for setting timers.
* time: simulation time when the interrupt will happen, it must smaller than current simulation time.
* code: intrrupt code, used to indicate different intterrupts.

### `Datapath` Class
#### send_msg(msg)
Send openflow packets to corresponding datapath(i.e., openflow switch).
* msg: openflow packet, no need to serialize the packet manually, this packet will be serialized automatically.

### `OpTimer` Class
Note: this class could be created anytime, all the OpTimer instances will share the timers.
#### set_op_timer(time, callback, user_data)
set a timer for calling the callback function in specific time, and the user_data will be passed to the callback unchanged.

* time: When the timer will be triggered, simulation time in second, absolute time from 0 and cannot smaller than current simulation time. Users can use `opsdn.sim_time() + xxx` for relative time, e.g., `opsdn.sim_time() + 10` means after 10s.
* callback: the function that will be called after timeout.function prototype: `callback(user_data)`，if this is a member function, it could be  `callback(self, user_data)`, see "opsdnpy/examples/topology_discovery.py" for example.
* user_data: The user defined data, it will be passed to the callback function unchanged.

**Note: APIs like openflow manipulations are compatible to the Ryu API, users are expected to reference and use Ryu APIs.**