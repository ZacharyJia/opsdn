# OPSDN-DLL-Bridge
[中文版](./README.zh.md)

This folder contains codes of the dll-bridge of opsdn.

## Motivations

Normally this dll-bridge is not needed, we could just create a Python virtual machine directly in the model to support the controller to run.
But unfortunately, OPNET has already embedded a very old version of Python(2.7) inside. This version has already not beed supported any more and Ryu cannot run on it.
Therefore we have to embed a new Python3 through this dll for isolation.

In summary, this dll will isolate the embedded Python2.7 and our Python3，which makes the python3 could run in OPNET.
Details could be find in the the technical report PDF file.


## Usage:
### Prebuild binary (Recommended):
1. Download the prebuilt binaries on the download page.
2. Extract them into a folder.
3. Add some environment varaibles:
- folder of opsdn.dll => PATH
- folder of opsdn.lib => LIB
- folder of your Python38.dll => PATH
4. Restart OPNET to make these env take effect.

### Build by your self:
1. Modify the `CMakeLists.txt` with your own Python3 `include` and `library` path.
2. Compile it.
3. Configure the environment variables as prebuilt binary.