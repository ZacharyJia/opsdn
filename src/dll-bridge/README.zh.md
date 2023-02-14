# OPSDN-DLL-Bridge
[English version](./README.md)


OPSDN的dll部分代码

## Motivations
其实正常来说是不需要这个dll的，直接在模型里创建Python虚拟机就行了。但是不知道OP是哪根筋搭错了，它会在内部嵌入一个Python2.7的版本，版本很老旧，并不想使用，并且已经失去支持。因此无奈，只能通过dll隔离一下，才能够嵌入一个新的Python3进来。

这个dll的基本作用就是隔离一下Python3的嵌入，提供C++和Python互相调用当中的上传下达的作用。
详细信息可以参考仓库中提供的Technical Report文件。

## 用法：
### 预编译版本（推荐）：
1. 从[Release页面](https://github.com/ZacharyJia/opsdn/releases)下载对应的预编译二进制文件。
2. 将下载得到的预编译二进制文件解压到一个文件夹当中。
3. 添加如下环境变量：
- opsdn.dll 所在目录 => PATH
- opsdn.lib 所在目录 => LIB
- 你自己的 Python38.dll 所在目录 => PATH
4. 重启OPNET使环境变量生效。

### 手动编译
1. 修改CMakeLists.txt文件，用你自己的Python3的include和library目录替换该文件中的路径。
2. 使用cmake编译。
3. 按照预编译版本的方式修改环境变量。