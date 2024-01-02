# 入门

### 头文件作用

函数名称 和 参数类型（用于索引查找函数地址）

## 生成静态库

就是 “生成构建文件”，如果 cpp 源码有错误的话，生成构建文件是没什么问题的。
只有在 “编译” 的时候 cpp 源码的错误 才会暴露出来。

```cmake
# ./xlog/CMakeLists.txt
# 先要限定最低版本
cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(xlog)

# 添加库，添加库的时候，不用xlog.o之类的，编译器会补充
add_library(xlog STATIC xlog.cc xlog.h)
```

### cmake -S （生成构建文件）

```sh
cmake -S . -B build
```

`cmake -S .`会搜索当前目录下的 cmakelists.txt

`-B build`表示：构建文件会在`./build/`目录下生成

构建文件有很多：

```sh
~/DOCs/cmakeLearn/notes/chap1/102cmake_lib/xlog/build » tree
.
├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.28.1
│   │   ├── CMakeCCompiler.cmake
│   │   ├── CMakeCXXCompiler.cmake
│   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   ├── CMakeSystem.cmake
│   │   ├── CompilerIdC
│   │   │   ├── CMakeCCompilerId.c
│   │   │   ├── CMakeCCompilerId.o
│   │   │   └── tmp
│   │   └── CompilerIdCXX
│   │       ├── CMakeCXXCompilerId.cpp
│   │       ├── CMakeCXXCompilerId.o
│   │       └── tmp
│   ├── CMakeConfigureLog.yaml
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeScratch
│   ├── Makefile.cmake
│   ├── Makefile2
│   ├── TargetDirectories.txt
│   ├── cmake.check_cache
│   ├── pkgRedirects
│   ├── progress.marks
│   └── xlog.dir
│       ├── DependInfo.cmake
│       ├── build.make
│       ├── cmake_clean.cmake
│       ├── cmake_clean_target.cmake
│       ├── compiler_depend.make
│       ├── compiler_depend.ts
│       ├── depend.make
│       ├── flags.make
│       ├── link.txt
│       └── progress.make
├── Makefile
└── cmake_install.cmake
```

### cmake --build （编译）

```sh
build > cmake --build .
```

如果在 build 目录下，可以直接`cmake --build .`

如果在项目目录下，需要指定目录`cmake --build build`（虽然上面也是指定目录）

于是乎，可以看到生成了一个`libxlog.a`文件

## 调用静态库

这个是最原始的方式，也就是已知项目路径的情况下，调用静态库

```cmake
# ./test_xlog/CMakeLists.txt

# 最低版本
cmake_minimum_required(VERSION 3.20)

project(test_xlog)

# 添加头文件路径，相当于是-i，../xlog 下有 xlog.h文件
include_directories("../xlog")

# 指定库查找路径，到那边去找。以当前cmakelists.txt的相对路径
link_directories("../xlog/build")

add_executable(test_xlog test_xlog.cc)

# 制定加载的库，找哪一个库
# 这个xlog库不用libxlog.a，只用原本的名字即可
# 注意一下，需要是生成可执行文件之后指定库
# 毕竟编译顺序是：先生成a.o，再链接的。还得看那本书《程序员的自我修养》
target_link_libraries(test_xlog xlog)
```

### 添加头文件路径 include_directories

```cmake
# 添加头文件路径，相当于是 gcc -i，../xlog 下有 xlog.h文件
include_directories("../xlog")
```

### 指定库的搜索路径

```cmake
# 指定库查找路径，到那边去找。以当前cmakelists.txt的相对路径
link_directories("../xlog/build")
```

### 生成可执行文件后，链接静态库

```cmake
# 制定加载的库，找哪一个库
# 这个xlog库不用libxlog.a，只用原本的名字即可
# 注意一下，需要是生成可执行文件之后指定库
# 毕竟编译顺序是：先生成a.o，再链接的。还得看那本书《程序员的自我修养》
target_link_libraries(test_xlog xlog)
```

## 动态库 + 库与调用在同一目录下

查看包含的动态库。

linux 下有命令：`ldd ./a.out`

mac 也有命令：`otool -L`

```sh
~/DOCs/cmakeLearn/notes/chap1/102cmake_lib/build » otool -L ./test_xlog
./test_xlog:
        @rpath/libxlog.dylib (compatibility version 0.0.0, current version 0.0.0)
        /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 1600.157.0)
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1336.61.1)
        /opt/homebrew/opt/llvm/lib/libunwind.1.dylib (compatibility version 1.0.0, current version 1.0.0)
```

在同一个文件中，既有"动态库"，又有"可执行文件"

```cmake
# CMakeLists.txt

# 指定最低版本
cmake_minimum_required(VERSION 3.20)

project(xlog)

# 头文件，这个头文件路径是一个全局的，xlog可以看见，test_xlog也可以看见
include_directories("./xlog")

# 生成动态库
add_library(xlog SHARED ./xlog/xlog.cc ./xlog/xlog.h)

# 生成可执行文件
add_executable(test_xlog ./test_xlog/test_xlog.cc)

# 链接
target_link_libraries(test_xlog xlog)
```

需要注意的是：这个`inclu_directories`是全局的。

这个`include_directories`就关系到：这个`test_xlog`中的`#include "xlog.h"`。

## windows 下的 动态库

```cpp
// xlog.h
#ifndef XLOG_H
#define XLOG_H

#ifdef xlog_EXPORT
    #define XCPP_API --declspec(dllexport)  // 导出xlog类的函数到lib文件中
#else
    #define XCPP_API --declspec(dllimport)
#endif

class XCPP_API XLog {
public:
    XLog();
};

#endif
```

## unix 下的 动态库

linux 下不认 windows 的 xlog_EXPORT

为了跨平台，可以这么写：

```cpp
// xlog.h
#ifndef XLOG_H
#define XLOG_H

#ifndef _WIN32
    // 这里是定义为 空
    #define XCPP_API
#else
    #ifdef xlog_EXPORT
        #define XCPP_API --declspec(dllexport)  // 导出xlog类的函数到lib文件中
    #else
        #define XCPP_API --declspec(dllimport)
    #endif
#endif

class XCPP_API XLog {
public:
    XLog();
};

#endif
```
