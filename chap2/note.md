# chap2 - cmake 常用功能

## cmake 注释

有 两种 注释的方法

1. 行注释

```cmake
# 这是一行注释
```

2. 括号注释

这种括号注释是：3.10 版本以上才支持的

```cmake
#[[中间的注释]]
```

## cmake message

```cmake
message("参数1")
message("参数p1" "参数p2" "p3" 123 测试)
```

（cmake 中，字符串 加 引号 不是必须的）

输出结果：

```sh
参数1
参数p1参数p2p3123测试
```

可见，message 中，是将参数直接 拼接 在了一起

### message 日志级别

#### 1. 不同的日志级别

TIPS：输出到不同的控制台 stdout（句柄是 1） 或 stderr（句柄是 2）( tlpi 中有 )

1. FATAL_ERROR --> 停止 cmake 运行和生成（进程退出，生成退出） --> stderr
2. SEND_ERROR --> cmake 继续运行，生成跳过（不生成 add_executable、add_library）（进程不退出，生成退出） --> stderr
3. WARNING --> stderr
4. (none)（没设置级别） or NOTICE --> stderr
5. STATUS --> 项目用户可能感兴趣的信息（比方说，哪个库编译成功了）
6. VERBOSE --> 针对项目用户的 详细 信息
7. DEBUG --> 给开发人员看的
8. TRACE --> 比 DEBUG 更详细

（需要 团队共同约定）

#### 2. message 设置 日志级别

1. 例子

```cmake
mesage(FATALE_ERROR "this is FATAL_ERROR")
```

2. (none) or NOTICE

下面两种效果是一样的

- (none)

mesage("this is NOTICE")

- NOTICE

mesage(NOTICE "this is NOTICE")

#### 3. 生成构建文件的时候，指定日志级别

```sh
cmake -S . -B build --log-level=VERBOSE
```

#### 4. 重定向

1. 默认的重定向

默认只会有 stdout 的重定向

```sh
cmake -S . -B build --log-level=VERBOSE > message.txt
```

这样，只是把我们的 stdout 输出到了 message.txt 中。
但是 stderr 依然是输出到了 控制台

2. stderr 重定向到 stdout

```sh
cmake -S . -B build --log-level=VERBOSE > message.txt 2>&1
```

### message reporting checks 查找库日志

查找库，3 个选项：

CHECK_START、CHECK_PASS、CHECK_FAIL

#### message 缩进（有涉及到变量）

1. 设置缩进

```cmake
set(CMAKE_MESSAGE_INDENT "--")
```

2. 取消缩进

```cmake
set(CMAKE_MESSAGE_INDENT "")
```

## cmake 变量（初步）

### 基本语法

1. 设置变量用`set(变量名 值1)`

可以有很多个值，有多个值的话，就变成了 list（暂时不会涉及）

2. 重复 set

重复 set 会覆盖之前的值

3. 释放变量

`unset(变量名)`

（这里暂时不会涉及到：缓存变量）

### 变量使用

#### 1. 解引用

```cmake
${变量名}
```

这个相当于是直接将：变量名 --> 替换成了 值

#### 2. 变量是可以嵌套的

```cmake
${${变量名}}
```

例如：

```cmake
set(VAR1 "this is var1")
set(VAR2 "VAR1")  # cmake中的基本类型就是字符串，也算是脚本语言的特性吧
message("VAR2 = ${VAR2}")
message("VAR2 = ${${VAR2}}")
```

#### 3. 变量名大小写敏感

#### 4. 变量是有作用域的（后面再说）

#### 5. 在字符串中直接使用

```cmake
message("VAR1 in string ${VAR1})
```

#### 6. 字符串转义

```cmake
message("VAR1 in string \${VAR1})
```

### 让 message 输出不同的颜色

\033[1;31;40m --> 1 高亮显示 ; 31 前景色红色 ; 40 背景色红色
\033[0m --> 0m 表示，取消颜色设置

这里的\033 是 8 进制 ascii（c 语言考过）

上面这两条`\033`是配对的

#### 常见 颜色设置 方法

```cmake
string(ASCII 27 Esc)

set(R "${Esc}[0;31m")
set(E "${Esc}[0m")  # 这个0有时候可以省略，因此也可以是：set(E "${ESE}[m")

message("${R}红色内容${E} 默认颜色")
message("${R}蓝色内容${E} 默认颜色")
```

这个 string 后面再讲

### cmake 内建变量（built-in variable）

#### 提供信息的变量

PROJECT_NAME

```cmake
# 1. 提供信息的变量
add_library(${PROJECT_NAME} ./xlog.h ./xlog.cc)
```

#### 改变行为的变量

BUILD_SHARED_LIBS <-- 这个变量还是一个 “缓存变量”

add_libray 如果没有设置 static 或者是 shared，
如果`BUILD_SHARED_LIBS=ON`-->创建 static，否则创建 shared

```cmake
# 2. 改变行为的变量
# 注意一下，这个BUILD_SHARED_LIBS是 缓存变量
set(BUILD_SHARED_LIBS ON)
```

#### 描述系统的变量

msvc、win32、android、unix

```cmake
# 3. 描述系统的变量
message("MSVC=" ${MSVC})
message("UNIX=" ${UNIX})
```

#### 控制构建过程的变量

cmake_color_makefile （改变 makefile 的颜色）

这里是：windows 的静态、动态库，调用、被调用

```cpp
#ifndef _Win32
    #define XCPP_API
#else // windows
    #ifdef xlog_STATIC
        #define XCPP_API
    #else
        #ifdef xlog_EXPORTS
            #define XCPP_API __declspec(dllexport)
        #else
            #define XCPP_API __declspec(dllimport)
        #endif
    #endif
#endif
```

传递宏

```cmake
# 4. 控制构建过程的变量：输出路径控制
# CMAKE_COLOR_MAKEFILE是否生成makefile的颜色，默认是ON
set(CMAKE_COLOR_MAKEFILE OFF)

# 传递变量给C++，静态库
add_definitions(-Dxlog_STATIC)
```

## include

比方说：可以搞一个类似于继承的东西，可以继承一个公共的约定，
生成文件的明明规范之类的。然后就可以在我们新建的项目中 include（继承） 这个 base cmakelists.txt

语法格式：

```cmake
include(file [OPTIONAL][RESULT_VARIABLE VAR])
```

如果指定了 optional 选项，那么如果 include 的文件不存在的话，也不会报错。

如果指定了 result_variable 选项，那么 var：1) include 的文件的绝对路径（成功） ; 2) NOTFOUND （失败，没有找到该文件）

### 示例（无 cpp）

一般情况下，将 include 放到 cmake 文件夹下。
跨文件的 include，可能会出现 变量的作用域 问题

```cmake
include("./cmake/test_cmake.cmake" OPTIONAL) # 文件不存在不报错
include("./cmake/test_cmake.cmake" OPTIONAL RESULT_VARIABLE ret) # 看看引用是否成功
message("RET = ${ret}")
```

就是有时候，一些`.cmake`是动态生成的，不包含还算是一个正常的事情

## 自动查找所有源码文件和头文件

目的：添加 头文件 和 代码 后不用修改 cmake。
但是如果是一些需要比较精细的工程，比方说：操作系统内核，
可能就不会使用自动化。

主要涉及一下两个函数：

### aux_source_directory

（aux 是辅助的意思）

```cmake
aux_source_directory("./src" LIB_SRCS)
```

会将 src 路径下所有源码存入 DIR_SRCS，但是不包含头文件

（aux_source_directory 并不会递归的搜索子目录）

cmake 代码示例：

```cmake
# 108auto_src_h/CMakeLists.txt

#[[ 目录结构
.
    CMakeLists.txt
    main.cc
    src
        xlog.cc
        xthread.cc
        xtest.c
    include
        xlog.h
        xthread.hpp
]]

cmake_minimum_required(VERSION 3.20)
project("auto_src_h")

# 头文件路径
include_directories("./include")

# 找到.目录下的源码，写入M_SRC
aux_source_directory("." M_SRC)
aux_source_directory("./src" SRC)

message("auto = ${M_SRC}")
message("auto = ${SRC}")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${M_SRC} ${SRC})
```

按照这种方式：

1. `include_directories`
2. `aux_source_directories`

会有一个问题：如果头文件更新了，并不会重新（惰性）。
但是我们是希望：头文件更新了，重新编译。

解决方案：FILE

```cmake
cmake_minimum_required(VERSION 3.20)
project("auto_src_h")

# 头文件路径
set(INCLUDE_PATH "./include")
include_directories("${INCLUDE_PATH}")

# 找到.目录下的源码，写入M_SRC
aux_source_directory("." M_SRC)
aux_source_directory("./src" SRC)

# 读取所有的头文件，读取.h，.hpp
file(GLOB H_FILE "{INCLUDE_PATH}/*.h*")

# 打印日志
message("M_SRC = ${M_SRC}")
message("SRC = ${SRC}")
message("H_FILE = ${H_FILE}")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${M_SRC} ${SRC} ${H_FILE})
```

### FILE

例如：

```cmake
FILE(GLOB H_FILE "${INCLUDE_PATH}/xcpp/*.h")
FILE(GLOB H_FILE_i "${INCLUDE_PATH}/*.h")
```

## cmake 命令实现程序的 分步生成

```sh
~/DOCs/cmakeLearn/notes/chap2/108auto_src_h/build (main) » cmake --build . --target help
The following are some of the valid targets for this Makefile:
... all (the default if no target is provided)
... clean
... depend
... edit_cache
... rebuild_cache
... auto_src_h
... main.o
... main.i
... main.s
... src/xlog.o
... src/xlog.i
... src/xlog.s
... src/xtest.o
... src/xtest.i
... src/xtest.s
... src/xthread.o
... src/xthread.i
... src/xthread.s
```

比方说，想要得到一个.cpp 的预处理文件，那么`cmake --build . --target main.i`（当前目录是 build），
那么就会得到`main.i`这个预处理以后的文件

### 突发奇想：反汇编 与 编译过程中的汇编 的区别

`gcc -S` 和 `objdump -d` 都可以用来生成汇编代码，但它们的工作方式和输出的内容有一些不同。

1. `gcc -S`：这个命令会将源代码（如 C 或 C++）编译成汇编代码，但不会进行链接。输出的是源代码级别的汇编，包含了源代码中的函数和变量名。

2. `objdump -d`：这个命令会将已经编译和链接过的二进制文件（如 ELF 文件）反汇编成汇编代码。输出的是机器级别的汇编，通常不包含源代码中的函数和变量名，而是包含了内存地址和机器指令。

所以，`gcc -S` 更适合于理解源代码是如何被编译成汇编的，而 `objdump -d` 更适合于理解已经编译和链接过的程序的机器级别的行为。

## cmake 调试，打印生成的具体指令
