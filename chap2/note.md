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

## 字符串

### 语法

#### 操作

##### 查找

语法：

```cmake
string(FIND <string> <substring> <out-var> [...])
```

示例：

```cmake
# 需求：取出begin和end之间的内容
set(STR1 "xxx begin test cmake string end xxxxxx")
# 查找开头字符串
set(BSTR "begin")
# 在 str1 中，查找 bstr 位置，存入b
string(FIND ${STR1} ${BSTR} b)
message("FIND ${BSTR} pos ${b}")
```

输出：

```sh
# 注意：cmake位置，以0开始
[cmake] FIND begin pos 4
```

示例：截取字符串

```cmake
string(FIND ${STR1} "end" e)
message("FIND end pos ${e}")
# 去掉begin字符位置
# 获取字符串长度
string(LENGTH ${BSTR} size)
math(EXPR b "${b}+${size}")
message("b = ${b}")
math(EXPR length "${e}-${b}")
message("length = ${length}")
# 获取子串
string(SUBSTRING ${STR1} ${b} ${length} substr)
message("substr = [${substr}]")
# 去掉空格
string(STRIP ${substr} substr)
message("substr = [${substr}]")
# 转成大写
string(TOUPPER ${substr} substr)
message("substr = [${substr}]")
```

输出：

```sh
[cmake] FIND begin pos 4
[cmake] FIND end pos 28
[cmake] b = 9
[cmake] length = 19
[cmake] substr = [ test cmake string ]
[cmake] substr = [test cmake string]
[cmake] substr = [TEST CMAKE STRING]
```

##### 追加、替换

```cmake
# 追加
string(APPEND substr "append01" "append02")
message("substr = [${substr}]")
# 替换
string(REPLACE "append" "REPLACE" substr ${substr})
message("substr = [${substr}]")
```

输出：

```sh
[cmake] substr = [TEST CMAKE STRINGappend01append02]
[cmake] substr = [TEST CMAKE STRINGREPLACE01REPLACE02]
```

##### 正则表达式匹配

```cmake
string(REGEX MATCH "[A-Z]+[0-9]+" output ${substr})
message("regex output = [${output}]")
```

输出：

```sh
[cmake] regex output = [STRINGREPLACE01]
```

#### json

cmake 中，多行字符串：

```cmake
set(
    multiStr
    [=[

    ]=]
)
```

语法：

```cmake
JSON
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         {GET | TYPE | LENGTH | REMOVE}
         <json-string> <member|index> [<member|index> ...])
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         MEMBER <json-string>
         [<member|index> ...] <index>)
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         SET <json-string>
         <member|index> [<member|index> ...] <value>)
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         EQUAL <json-string1> <json-string2>)
```

示例：

```cmake
set(
    tjson
    [=[
        {
            "webs" : {
                "web" : [
                    {"name": "cmake", "url":"cmake.org.cn"},
                    {"name": "ffmpeg", "url":"ffmpeg.club"}
                ]
            }
        }
    ]=]
)
message(${tjson})
# 访问webs.web[0].name
string(JSON var ERROR_VARIABLE evar GET ${tjson} webs web 0 name)
message("var = ${var}")
```

- 如果有错误：

1. 没有数据成员：evar = webs web2 not found

2. 如果是 json 的格式错误：

```sh
[cmake] evar = failed parsing json string: * Line 5, Column 27
[cmake]   Missing ',' or ']' in array declaration
```

- 如果没有错误

```sh
evar = NOTFOUND
```

##### json 数组的长度

```cmake
# 读取json数组长度
string(
    JSON
    web_count
    ERROR_VARIABLE evar
    LENGTH
    ${tjson} webs web
)
message("JSON LENGTH = ${web_count}")
```

##### json 的增加与修改（set）

```cmake
string(
    JSON
    modified_json
    ERROR_VARIABLE evar
    SET
    # 下标是2
    ${tjson} webs web 2 [=[
        {"name":"cpp", "url":"cppreference.com"}
    ]=]
)
message("modified_json = ${modified_json}")
```

输出：

```sh
[cmake] modified_json = {
[cmake]   "webs" :
[cmake]   {
[cmake]     "web" :
[cmake]     [
[cmake]       {
[cmake]         "name" : "cmake",
[cmake]         "url" : "cmake.org.cn"
[cmake]       },
[cmake]       {
[cmake]         "name" : "ffmpeg",
[cmake]         "url" : "ffmpeg.club"
[cmake]       },
[cmake]       {
[cmake]         "name" : "cpp",
[cmake]         "url" : "cppreference.com"
[cmake]       }
[cmake]     ]
[cmake]   }
[cmake] }
```

##### json 的删除

```cmake
string(
    JSON
    remove_json
    ERROR_VARIABLE evar
    REMOVE
    ${tjson} webs web 1
)
message("removed_json = ${remove_json}")
```

删除：

```sh
[cmake] removed_json = {
[cmake]   "webs" :
[cmake]   {
[cmake]     "web" :
[cmake]     [
[cmake]       {
[cmake]         "name" : "cmake",
[cmake]         "url" : "cmake.org.cn"
[cmake]       }
[cmake]     ]
[cmake]   }
[cmake] }
```

## list 基础用法

### list 变量初始化 及 长度

cmake 中存储的所有值都是字符串，有`;`间隔符的字符串被拆分成列表

```cmake
set(src "a" "b" "c" "d;e")
message("src = ${src}") # a;b;c;d;e
list(LENGTH src len)
message("src length = ${len}")
```

输出：

```sh
[cmake] src = a;b;c;d;e
[cmake] src length = 5
```

### list 追加写入

```cmake
# list追加
list(APPEND src "g")
list(APPEND src "h;i")
message("src = ${src}")
list(LENGTH src len)
message("src length = ${len}")
```

### 对 list 的访问

```cmake
# list访问 下标访问：0 1 2 3 ... -1 -2 -3 ...
list(GET src 1 var)
message("GET src 1 = ${var}")
list(GET src -1 var)
message("GET src -1 = ${var}")
```

输出：

```sh
[cmake] GET src 1 = b
[cmake] GET src -1 = i
```

### list 拼接，或者是用不同的方式分隔

```cmake
list(JOIN src "|" var)
message("JOIN src = ${var}")
```

输出：

```sh
[cmake] JOIN src = a|b|c|d|e|g|h|i
```

### 取其中一部分数组

```cmake
list(SUBLIST src 0 3 var)
message("SUBLIST ${var}")
```

输出：

```sh
[cmake] SUBLIST a;b;c
```

### 查找

```cmake
list(FIND src "d" var)
message("FIND ${var}")
```

输出：

```sh
[cmake] FIND 3
```

### 插入

```cmake
# 插入节点 a;b;c;d;e;f;g;h;i
list(INSERT src 4 "d1")
list(INSERT src 2 "b1")
message("insert src ${src}")
```

输出：

```sh
[cmake] insert src a;b;b1;c;d;d1;e;g;h;i
```

### 删除元素

```cmake
list(REMOVE_ITEM src "b")
message("remove src = ${src}")
```

输出：

```sh
[cmake] remove src = a;b1;c;d;d1;e;g;h;i
```

这种`remove_item`是：删除所有的匹配的

### 修改

通过`find`，然后删除指定位置，再插入指定位置

### list 队列操作方式

#### 出队

这里的 list 是双向队列

```cmake
# 后端出队
# src = a;b1;c;d;d1;e;g;h;i
list(POP_BACK src var)
message("pop_back ${var}")
message("pop_back ${src}")
```

同理，前端出队是：`pop_front`

输出：

```sh
[cmake] pop_back i
[cmake] pop_back a;b1;c;d;d1;e;g;h
```

#### 入队

1. 前端：直接`insert 0`即可

2. 后端：直接`append`即可

### 去重

```cmake
# 去重
set(rsrc "1;2;3;3;2;1;1;2;3;4;5;6;7")
message("rsrc before = ${rsrc}")
list(REMOVE_DUPLICATES rsrc)
message("rsrc after = ${rsrc}")
```

输出：

```sh
[cmake] rsrc before = 1;2;3;3;2;1;1;2;3;4;5;6;7
[cmake] rsrc after = 1;2;3;4;5;6;7
```

### list 数据排序

```cmake
set(arr "8;12;5;7;9;3")
list(SORT arr)
message("message = ${arr}")
```

输出：

```sh
[cmake] arr = 12;3;5;7;8;9
```

这里有问题，为什么 12 在 3 前面，因此这里是按照：字典序

```cmake
# 指定排序方式：自然数排序
list(SORT arr COMPARE NATURAL)
message("arr = ${arr}")
```

## cmake foreach 循环
