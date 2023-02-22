# opsdnpy

A python package for OPSDN. This folder contains the python part of OPSDN.

See [OPSDN](https://github.com/zacharyjia/OPSDN) for details.


## Structures

- `app_manager.py`: A container to hold all the apps that are enabled in the controller.
- `app.py`: Here we provide 2 decorators for making a python class `controller app` and a method `event handler`.
- `basic_app.py`: A basic app for building the secure channel between the controller and OpenFlow switches.
- `controller.py`: A basic controller class, which will dispatch packets from OPNET to the Datapaths. Your controller class should be a subclass of it.
- `data_path.py`: Datapath class for dispatching packets, sending packets, etc.
- `op_timer.py`: A timer class that enables the controller to have the ability to run code regularly.
