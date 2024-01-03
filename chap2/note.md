# chap3 - cmake 主要语法

## if 控制流程

### 语法格式

```cmake
if (<condition>)
    <commands>
elseif (<condition>)
    <command>
else()
    <command>
endif()
```

### 基本表达式

cmake if 基本表达式，也就是`<condition>`可以有什么

1. `<constant>`常量

ON, YES, TRUE, Y 或者 非零数（包括浮点数） --> TRUE

0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串，或者以 NOTFOUND 结尾 --> FALSE

2. `<variable>`变量

非 FALSE 且 已被定义 --> TRUE

1)FLASE 或者 2)未定义 变量、环境变量 --> FALSE

宏参数 不是变量（宏只是替换）

3. `<string>`字符串

字符串的值是常量 TRUE --> TRUE

其他带引号的字符始终计算为 FALSE（不认识）

### 逻辑运算符

1. `NOT`

2. `AND`

3. `OR`

4. 复合：(condition1) AND (condition2 OR condition3)

### if 判断语句

#### 一元判断

1. EXISTS 用来检查一个 文件 或 目录 是否存在

2. COMMAND 检查一个 命令 或者 函数 是否存在

3. DEFINED 判断变量是否被定义

#### 二元判断

1. （变量） QEUAL LESS LESS_EQUAL GREATER GREATER

可以跨类型进行判断

```cmake
# 数字判断
set(VAR1 123)
if(VAR1 EQUAL "123")
    message("VAR1 equal 123")
endif()
```

2. （字符串） STREQUAL STRLESS STRLESS_EQUAL STRGREATER STRGREATER_EQUAL

3. （版本号的判断）VERSION_EQUAL VERSION_LESS VERSION_LESS_EQUAL VERSION_GREATER VERSION_GREATER_EQUAL

4. MATCHES，这个支持正则表达式

比方说，我们可能会开放用户输入之类的，
我们可以通过正则表达式，看看用户的输入是否正确

```cmake
# 匹配上了
if("abcd123" MATCHES "[a-z]+")
    message("is match")
endif()
```

```cmake
# 没有匹配上
if("abcd123" MATCHES "^[a-z]+$")
    message("is match")
else()
    message("is not match")
endif()
```

#### 存在性检查

#### 文件操作

#### 比较

#### 版本比较

### 遗留问题

1. 判断语句过长
2. 无法嵌入其他的函数中

## 变量 与 缓存

1. 缓存下来，写入 cmake 生成的一系列文件中。再次生成的时候，不会重复生成
2. 全局性质，多个文件可以共享

cache 覆盖策略设置

缓存变量对应 cmake-gui 和 ccmake

cmake 内置缓存变量，比方说之前用到的 BUILD_SHARED_LIBS

-D 传递缓存变量

### 缓存变量的基础语法 和 使用

```cmake
set(<variable> <value> CACHE <type> <docstring> [FORCE])
```

- 缓存变量，需要加`CACHE`
- type 表示 缓存变量的类型
  - BOOL ON/OFF 选择框
  - FILEPATH 文件选择
  - PATH 目录选择
  - STRING
  - INTERNAL
- docstring 说明
- FORCE 强制修改

强制修改的意思就是，如果我们第一次设置成了 001，第二次设置成了 002，
如果我们不加 FORCE，那么就不会覆盖

缓存变量，只要生成了 build 文件，甚至是把变量的定义给删除了，
依然可以访问变量。

```cmake
cmake_minimum_required(VERSION 3.20)
project(cmake_cache)

# 设置缓存变量的类型，对应于string类型
set(var1 "CACHE var1 value" CACHE STRING "cache doc")

set(var1 "CACHE var1 value1-1" CACHE STRING "cache doc")
set(var1 "CACHE var1 value1-2" CACHE STRING "cache doc")

message("var1 = ${var1}") # 输出 cache var1 value
```

强制修改：

```cmake
cmake_minimum_required(VERSION 3.20)
project(cmake_cache)

# 设置缓存变量的类型，对应于string类型
set(var1 "CACHE var1 value" CACHE STRING "cache doc")

set(var1 "CACHE var1 value1-1" CACHE STRING "cache doc")
set(var1 "CACHE var1 value1-2" CACHE STRING "cache doc" FORCE)

message("var1 = ${var1}") # 输出 cache var1 value1-2
```

### cache 变量的 作用域 是 全局 的

普通变量的一个性质：

1. 父节点 无法获取 子节点生成的变量 （但是子节点可以获取父节点生成的变量）
2. 兄弟之间，无法获取生成的变量

缓存变量：

缓存变量是全局的

### cmake-gui

缓存变量的一个功能就是：让用户决定编译的选项

![cmake-gui](./image/cmake-gui.png)

这个 cmake-gui 就可以看到我们的缓存变量

### option

就是 cache 变量的很多场景是让用户自己配置，
这个自己配置呢，又有很多是：bool 类型的，
bool 类型有一种简化的版本 --> option

```cmake
option(OPT1 "opt1 doc" OFF)
```

这个就相当于是：

```cmake
set(OPT1 OFF CACHE BOOL "top1 doc")
```

### ccmake

ccmake 是用于修改 cache 的，
修改 cache 就要先保证：我们已经有了 cache

打开 cache 路径

```cmake
~/DOCs/cmakeLearn/notes/chap2/202cmake_cache (main*) » ccmake build
```

### cmake cache 覆盖策略设置

普通变量 可能与 cache 变量冲突（重名）

```cmake
# 普通变量
set(NVAR1 "normal var1")

# cache变量
set(NVAR1 "cache var1" CACHE STRING "cache doc")

message("NVAR1 = ${NVAR1}") # cache var1
```

或者是可以直接查找 cache 变量：

```cmake
message("NVAR1 = ${NVAR1}") # cache var1
message("NVAR1 = $CACHE{NVAR1}") # cache var1
```

这个我自己运行的时候很有问题，
第一个有时候是`normal`，有时候是`cache`

默认情况下，如果没有强调`cache`（也就是第二种访问方式），
先会查找普通变量，再会查找 cache 变量（这就是一种策略）

改变策略

```cmake
# 设置缓存变量 覆盖 同名普通变量 的策略
cmake_policy(SET CMP0126 OLD)
```

`old`表示：会删除普通变量

`new`表示：有限访问 normal，只有 强调了`$CACHE` 才会访问 缓存变量 （默认）

```cmake
cmake_policy(SET CMP0126 NEW)
set(NVAR1 "normal var1")
set(NVAR1 "cache var1" CACHE STRING "cache doc")
message("NVAR1 = ${NVAR1}") # --> normal
message("NVAR1 = $CACHE{NVAR1}") # --> cache
```

### 传递 缓存变量

```cmake
# 用户传递的变量
message("para1 = ${PARA1}")
```

```sh
~/DOCs/cmakeLearn/notes/chap2/202cmake_cache (main*) » cmake -S . -B build -D PARA1=para001
```

#### 例子：

动态库，静态库

传递：

```sh
cmake -S . -B build -D BUILD_SHARED_LIBS=ON
```

当然 cache 一定要注意，就是修改了 cmakelists.txt，
变量不一定会改变

这个就像是 函数式编程 的极端反面：每次运行，甚至都有之前运行的状态

## 属性 与 变量

属性就相当于是：成员变量;
而 “变量” 就相当于是：全局变量（尽管上面提到了，变量不一定是全局的，注意作用域）

全局属性：没有 cache 的全局变量

### 属性语法

#### 设置属性 set_property

```cmake
set_property(<GLOBAL                      |
              DIRECTORY [<dir>]           |
              TARGET    [<target1> ...]   |
              SOURCE    [<src1> ...]  # 源码有很多选项
                        [DIRECTORY <dirs> ...]
                        [TARGET_DIRECTORY <targets> ...] |
              INSTALL   [<file1> ...]     |
              TEST      [<test1> ...]
                        [DIRECTORY <dir>] |
              CACHE     [<entry1> ...]    >
              # 作用域，可以有很多选项
             [APPEND] [APPEND_STRING]
             PROPERTY <name> [<value1> ...])
```

文档中，`<>`尖括号表示：必须; `[]`中括号表示：可选

#### 读取属性 get_property

```cmake
get_property(<variable>  #
             <GLOBAL             |  # 从某一个作用域中读取属性
              DIRECTORY [<dir>]  |
              TARGET    <target> |
              SOURCE    <source>
                        [DIRECTORY <dir> | TARGET_DIRECTORY <target>] |
              INSTALL   <file>   |
              TEST      <test>
                        [DIRECTORY <dir>] |
              CACHE     <entry>  |
              VARIABLE           >
             PROPERTY <name>
             [SET | DEFINED | BRIEF_DOCS | FULL_DOCS])
```

因为 cmake 中并没有返回值这个概念，
所以读取的属性是存放到一个变量中

#### define_property

定义属性的名称

```cmake
define_property(<GLOBAL | DIRECTORY | TARGET | SOURCE |
                 TEST | VARIABLE | CACHED_VARIABLE>
                 PROPERTY <name> [INHERITED]
                 [BRIEF_DOCS <brief-doc> [docs...]]
                 [FULL_DOCS <full-doc> [docs...]]
                 [INITIALIZE_FROM_VARIABLE <variable>])
```

#### 示例（全局）

全局属性（相当于是没缓存的全局变量）

```cmake
# 添加子目录
add_subdirectory("./sub1")

# 获取子目录的全局属性
get_property(
    val_sub1
    GLOBAL
    PROPERTY TEST_sub1
)

message("test sub1 = ${val_sub1}")
```

#### 示例（append）

```cmake
# append append_string
set_property(
    GLOBAL
    APPEND
    PROPERTY test_append
    "append 001"
)
set_property(
    GLOBAL
    APPEND # 这里的append表示数组的方式添加
    PROPERTY test_append
    "append 002"
)
get_property(
    val2
    GLOBAL
    PROPERTY test_append
)
message("test_append = ${val2}") # --> append001;append 002
```

除了使用 数组方式追加（append），
还可以：字符串方式追加(append_string)

#### get_property set | defined

get_property 最后的参数，意思是：是否被 set，或者是否被定义

```cmake
get_property(
    var3
    GLOBAL
    PROPERTY p1
    DEFINED
)
message("p1 = ${var3}") # p1 = 0
```

这里，只有：p1 被定义，也就是调用了`define_property`以后，才为 1。
即使是`set`也不算是`defined`（感觉这个有点奇怪）。
这个就像是：c 语言，声明了变量，但是没有传值

```cmake
define_property(
    GLOBAL
    PROPERTY test_def
    BRIEF_DOCS "p1 brief doc"
)

get_property(
    var4
    GLOBAL
    PROPERTY test_def
    DEFINED
)
message("p1 = ${var4}")
```

### 属性分类

#### 1. 全局属性

#### 2. 目录属性

#### 3. 文件属性

给文件加属性，可以给源文件传入 “宏变量”

```cmake
# 文件属性
set_property(
    SOURCE main.cc
    PROPERTY s1
    "s1 value"
)
get_property(
    var7
    SOURCE main.cc
    PROPERTY s1
)
message("var7 = ${var7}")

# cmake传递变量给C++
# cmake通过 compile_definitions 传递 宏变量
set_property(
    SOURCE main.cc
    PROPERTY COMPILE_DEFINITIONS
    "PARA1=1234" # 相当于 -DPARA1 1234
)

add_executable(${PROJECT_NAME} ./main.cc)
```

#### 4. 目标属性

这个要比给文件设置属性要灵活很多

比方说，我们要生成 release（-O3） 和 debug（-g 以及关闭返回值优化） 版本的目标，
需要的属性肯定是不同的

```cmake
add_executable(${PROJECT_NAME} ./main.cc)
# 给C++传递 宏变量
set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY COMPILE_DEFINITIONS
    "PARA2=\"sdfsdfsdf\""
)
set_property(
    TARGET ${PROJECT_NAME}
    APPEND # 数组追加的方式
    PROPERTY COMPILE_DEFINITIONS
    "PARA3=\"test para3\""
)
```

我们要先有：目标，再为目标设置属性

上面，如果不是追加的话，那么就会覆盖前面的 set

### 打印属性

前面的打印有些繁琐：先`get_property`，再`message`

cmake 提供了方法，可以让我们打印多个属性`cmake_print_properties`

也有打印多个变量的方法：`cmake_print_variables`

打印需要引入 cmake 的一个模块`include()`

打印：

```cmake
# 打印属性
include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS ${PROJECT_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS
    TVAR
)
```

输出：

```sh
Properties for TARGET cmake_cache:
    cmake_cache.COMPILE_DEFINITIONS = "PARA2="sdfsdfsdf";PARA3="test para3""
    cmake_cache.TVAR = "tval"
```

## 环境变量

### 环境变量语法

```cmake
set(ENV{<variable>} <value>)
```

访问的时候：

（就像 cache 变量一样）

```cmake
$ENV{<variable>}
```

### 环境变量特性

只会影响当前 cmake 进程，不影响调用 cmake 的进程，
也不影响整个系统环境，也不影响后续构建或测试进程的环境

只在 "生成构建文件" 的时候会用到

环境变量与全局属性差不多（不缓存），
但是 访问方式，设置方式要比属性简单

### 环境变量类型

1. cmake 预值
2. 自定义环境变量
3. 系统变量（操作系统的环境变量）

### 示例

```cmake
set(ENV{MYENV} "test env value")
message("MYENV = $ENV{MYENV}")
```

全局性也是可以验证的

#### 系统环境变量

```sh
~/DOCs/cmakeLearn/notes/chap1/108auto_src_h/build (main*) » env
```

通过系统的环境变量，可以知道很多信息的

```cmake
message("username = $ENV{USER}")
```

输出：

```sh
[cmake] username = wangfiox
```

## cmake math 数学运算

语法格式：

```cmake
math(EXPR <variable> "<expression>" [OUTPUT_FORMAT <format>])
```

1. `EXPR <variable>`相当于是返回值（cmake 中没有返回值）
2. `<expression>`可以解引用
3. `[OUTPUT_FORMAT<format>]`可以十进值，十六进制的输出
4. 运算结果必须是 64 位有符号整数
5. 运算符

### 示例：

```cmake
set(expr "(2*10) + 5")
math(EXPR out ${expr} OUTPUT_FORMAT HEXADECIMAL)
message("out = ${out}")
```

输出：

```sh
[cmake] out = 0x19
```
