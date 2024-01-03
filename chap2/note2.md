# chap3 - cmake 主要语法

## cmake foreach 循环

### 语法

```cmake
foreach(<loop_var> <items>)
  <commands>
endforeach([<loop_var>])
```

#### RANGE

```cmake
foreach(<loop_var> RANGE <stop>)
```

或者是

```cmake
foreach(<loop_var> RANGE <start> <stop> [<step>])
```

#### IN

对数组的操作：

1. LISTS：传入的是变量名

```cmake
foreach(num IN LISTS arr)
```

2. ITEMS：相当于是`${list}`

```cmake
foreach(num IN ITEMS "1;2;3;4;5")
```

3. ZIP_LISTS：一次遍历多个 list

```cmake
set(arr1 "1;3;5;7;9")
set(arr2 "2;4;6;8;10")

foreach(num IN ZIP_LISTS arr1 arr2)
    message("num_0 = ${num_0}")
    message("num_1 = ${num_1}")
endforeach(num IN ZIP_LISTS arr1 arr2)
```

最后这个 ZIP_LISTS 可以用两个迭代变量：

```cmake
foreach(var1 var2 IN ZIP_LISTS arr1 arr2)
```

#### break 和 continue

需求：3 的倍数，输出，否则输出.

```cmake
foreach(var RANGE 100)
    math(EXPR re "${var} %3")

    if(re EQUAL 0)
        message(${var})
        continue()
    endif()

    message(".")

    if(var GREATER 50)
        break()
    endif()
endforeach(var RANGE 100)
```

## cmake while 循环

首先，我们的 cmake 是用来 编译的，不是用来构建红黑树的（bushi），
因此是不推荐有 “死循环” 的

```cmake
while(var)
    math(EXPR var "${var} + 1")
    math(EXPR re "${var} % 10")

    if(re)
        continue()
    endif()

    message(${var})

    if(var GREATER 100)
        set(var 0)
    endif()
endwhile(var)
```

## cmake 宏 macro

（后续会讲 函数）

### 基本语法

```cmake
macro(<name> [<arg1> ...])
  <commands>
endmacro()
```

宏 大小写 不敏感

也就是：FOO()，Foo()，foo() 都是一回事

cmake 官方约定是：都使用 小写

两种调用方式：

1. foo() <-- 一般用这种
2. cmake_language(CALL foo)

### 普通参数

1. 必须的参数

如果我们的宏，设置成了：`macro(foo arg1 arg2)`

那么我们调用这个宏的时候，至少传递两个参数，可以多传

2. ARGC 参数的个数（宏里面可以看到我们参数的个数）

3. ARGN 参数数组

4. 参数的位置：ARGV0 ARGV1 ARGV2

5. 参数不是变量（宏 与 函数 的区别）

无法使用如下代码：

- `if (ARGV1)`
- `if (DEFINED ARGV2)`
- `ARGC GREATER 2`
- `foreach(loop_var IN LISTS ATGN)`

如果需要这么做：请加入`${}`（这是一个坑）

如果在调用宏的范围内，有一个同名的变量，则使用未引用的名称讲使用现有的变量而不是参数 --> 意思就是：尽量不要同名

#### 5. 宏参数不是变量

```cmake
macro(foo arg1 arg2)
    message("arg1 = ${arg1} arg2=${arg2}")

    if(arg1)
        message("== arg1 true ==")
    else()
        message("== arg1 false ==")
    endif()

    if(${arg1})
        message("== \$\{arg1\} true ==")
    else()
        message("== \$\{arg1\} false ==")
    endif()
endmacro(foo ar1 arg2)

foo(123 "test")
```

输出：

```sh
[cmake] arg1 = 123 arg2=test
[cmake] == arg1 false ==
[cmake] == ${arg1} true ==
```

#### 2. ARGC ARGN ARGV0 ARGV1 ...

```cmake
macro(foo2)
    # 参数数量
    message("ARGC = ${ARGC}")

    # 参数list
    message("ARGN = ${ARGN}")

    foreach(var IN ITEMS ${ARGN})
        message("var = ${var}")
    endforeach(var IN ITEMS ${ARGN})

    message("ARGV2 = ${ARGV2}")
endmacro(foo2)

foo2(1 2 123 "foo")
```

这里注意一下：foreach 里面应该是 ITEMS：
首先，ARGN 不是变量，因此不能直接`foreach(var IN LISTS ARGN)`;
其次，`${ARGN}`就已经是字面量了，应该用`ITEMS`的访问方式

输出：

```sh
[cmake] ARGC = 4
[cmake] ARGN = 1;2;123;foo
[cmake] var = 1
[cmake] var = 2
[cmake] var = 123
[cmake] var = foo
[cmake] ARGV2 = 123
```

### 属性式参数

我们可以看见，很多 cmake 的语法都有 “属性式参数”

比方说，之前的 json

```cmake
string(
    JSON
    web_count
    ERROR_VARIABLE evar
    LENGTH
    ${tjson} webs web
)
```

这里的`ERROR_VARIABLE`就是一种属性

比方说，我们希望可以接受这样的调用：`my_macro(TARGETS foo bar DESTINATION bin)`

我们解析参数需要用到：cmake_para_arguments，这里注意一个英语的细节：arguments 表示实参

#### cmake_parse_arguments

语法格式：

```cmake
cmake_parse_arguments(<prefix> <options> <one_value_keywords>
                      <multi_value_keywords> <args>...)
```

- `<prefix>` 生成变量的前缀
- `<options>` 设置了就是 true，没有设置就是 false，不用赋值
- `<one_value_keyword>` 单个值的变量
- `<multi_value_keywords>` 多个值的变量
- `_UNPARSED_ARGUMENTS` 传递了错误的值
- `_KEYWORDS_MISSING_VALUES` 没有设定值

##### 前缀 与 options

加前缀的目的是：防止与环境中的一些变量发生冲突

```cmake
macro(my_parse)
    message("ARGN = ${ARGN}")
    cmake_parse_arguments(
        "MY" # 前缀
        "LOG;FILE" # options
        "BIN;LIB" # 单值
        "" # 多值
        ${ARGN} # 参数数组
    )
    message("MY_LOG = ${MY_LOG}")
    message("MY_FILE = ${MY_FILE}")
endmacro(my_parse)

my_parse(LOG)
```

输出：

```sh
[cmake] ARGN = LOG
[cmake] MY_LOG = TRUE
[cmake] MY_FILE = FALSE
```

##### 单值 多值的传递

```cmake
macro(my_parse)
    message("ARGN = ${ARGN}")
    cmake_parse_arguments(
        "MY" # 前缀
        "LOG;FILE" # options
        "BIN;LIB" # 单值
        "TARGETS" # 多值
        ${ARGN} # 参数数组
    )
    message("MY_LOG = ${MY_LOG}")
    message("MY_FILE = ${MY_FILE}")
    message("MY_BIN = ${MY_BIN}")
    message("MY_LIB = ${MY_LIB}")
    message("MY_TARGETS = ${MY_TARGETS}")
endmacro(my_parse)

my_parse(
    LOG
    BIN "mybin"
    TARGETS "ta1" "ta2" "ta3"
)
```

输出：

```sh
[cmake] ARGN = LOG;BIN;mybin;TARGETS;ta1;ta2;ta3
[cmake] MY_LOG = TRUE
[cmake] MY_FILE = FALSE
[cmake] MY_BIN = mybin
[cmake] MY_LIB =
[cmake] MY_TARGETS = ta1;ta2;ta3
```

##### 传值 出现 错误

可以知道错误传递的参数：`MY_UNPARSED_ARGUMENTS `

```cmake
macro(my_parse)
    message("ARGN = ${ARGN}")
    cmake_parse_arguments(
        "MY" # 前缀
        "LOG;FILE" # options
        "BIN;LIB" # 单值
        "TARGETS" # 多值
        ${ARGN} # 参数数组
    )
    message("MY_LOG = ${MY_LOG}")
    message("MY_FILE = ${MY_FILE}")
    message("MY_BIN = ${MY_BIN}")
    message("MY_LIB = ${MY_LIB}")
    message("MY_TARGETS = ${MY_TARGETS}")
    message("MY_UNPARSED_ARGUMENTS = ${MY_UNPARSED_ARGUMENTS}")
endmacro(my_parse)

my_parse(
    LOG "mylog"  # 这个 LOG 是不用接受参数的，只要在参数列表中LOG=TRUE
    BIN "mybin"
    TARGETS "ta1" "ta2" "ta3"
)
```

输出：

```sh
[cmake] ARGN = LOG;mylog;BIN;mybin;TARGETS;ta1;ta2;ta3
[cmake] MY_LOG = TRUE
[cmake] MY_FILE = FALSE
[cmake] MY_BIN = mybin
[cmake] MY_LIB =
[cmake] MY_TARGETS = ta1;ta2;ta3
[cmake] MY_UNPARSED_ARGUMENTS = mylog
```

##### 缺省的 传值

```cmake
macro(my_parse)
    message("ARGN = ${ARGN}")
    cmake_parse_arguments(
        "MY" # 前缀
        "LOG;FILE" # options
        "BIN;LIB" # 单值
        "TARGETS" # 多值
        ${ARGN} # 参数数组
    )
    message("MY_LOG = ${MY_LOG}")
    message("MY_FILE = ${MY_FILE}")
    message("MY_BIN = ${MY_BIN}")
    message("MY_LIB = ${MY_LIB}")
    message("MY_TARGETS = ${MY_TARGETS}")
    message("MY_UNPARSED_ARGUMENTS = ${MY_UNPARSED_ARGUMENTS}")
    message("MY_KEYWORDS_MISSING_VALUES = ${MY_KEYWORDS_MISSING_VALUES}")
endmacro(my_parse)

my_parse(
    LOG
    BIN "mybin"
    LIB # 需要传一个值，但是没有
    TARGETS "ta1" "ta2" "ta3"
)
```

输出：

```sh
[cmake] ARGN = LOG;BIN;mybin;LIB;TARGETS;ta1;ta2;ta3
[cmake] MY_LOG = TRUE
[cmake] MY_FILE = FALSE
[cmake] MY_BIN = mybin
[cmake] MY_LIB =
[cmake] MY_TARGETS = ta1;ta2;ta3
[cmake] MY_UNPARSED_ARGUMENTS =
[cmake] MY_KEYWORDS_MISSING_VALUES = LIB
```

## cmake 函数

1. 函数的参数是变量
2. 函数内部设置的普通变量，作用域只在函数内
3. 函数可以用 return 返回

### function 参数是变量

函数的参数是变量，因此可以在`if`和`foreach`中使用，不用`${}`

```cmake
function(func1 arg1 arg2)
    message("IN function func1")
    message("arg1 = ${arg1}")
    message("arg2 = ${arg2}")

    if(arg1)  # 不用${}
        message("arg1 == TRUE")
    else()
        message("arg1 != FALSE")
    endif()

    foreach(var IN LISTS arg1)  # 不用 ${}
        message("var = ${var}")
    endforeach(var IN LISTS arg1)
endfunction(func1 arg1 arg2)

func1("1;2;3;4;5" 2)
```

### 作用域

cmake 的函数，在函数内部是可以访问 父作用域 的变量，但是不能修改

如果 父作用域变量 与 形参 同名，优先使用 形参（shallow）

不能修改父作用域的 变量，如果 同名，相当于是创建了一个新的变量

```cmake
function(func_var arg1)
    message("in func_var ${arg1}")
    message("var1 = ${var1}")
    set(var1 "func var")
endfunction(func_var arg1)

set(var1 "main1")
set(arg1 "main arg1")
func_var(123)
message("var1 = ${var1}")
```

输出：

```sh
[cmake] in func_var 123
[cmake] var1 = main1
[cmake] var1 = main1
```

### return

宏中不能使用`return`，这样就代表的是全局作用域的`return`（因为宏是直接复制的）

cmake 中的 return，只是为了让过程块提前结束，
并不会真的返回某个值

function 如果要返回某一个值，可以：

```cmake
function(my_function result_var)
    set(${result_var} "my result" PARENT_SCOPE)
endfunction()
```

macro 如果要返回一个值，可以设置一个 ret 变量

### parent_scope

好奇，既然这个可以扩大到 父作用域，
那么子目录的 parent_scope 能不能到 父作用域 呢？

1. 可以访问子目录中的函数

```cmake
add_subdirectory("./sub1")
func_sub(123)
```

2. 父作用域（注意一下）

子目录下：

```cmake
# ./sub1/cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(sub1)

function(func_sub1)
    math(EXPR sub1_var "${sub1_var} + 1")
    message("in func_sub1: sub1_var = ${sub1_var}")
    set(sub1_var ${sub1_var} PARENT_SCOPE)
endfunction(func_sub1)

func_sub1()
func_sub1()
message("in sub1: sub1_var = ${sub1_var}")
```

主目录下：

```cmake
# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_macro)
add_subdirectory("./sub1")
message("===========================")
func_sub1()
message("in main: sub1_var = ${sub1_var}")
```

子目录没有将 sub1_var 扩大作用域，
因此 父目录 与 子目录 的 sub1_var 实际上是不同的内存的

输出为：

```sh
[cmake] in func_sub1: sub1_var = 1
[cmake] in func_sub1: sub1_var = 2
[cmake] in sub1: sub1_var = 2
[cmake] ===========================
[cmake] in func_sub1: sub1_var = 1
[cmake] in main: sub1_var = 1
```

但是如果我们将子目录的最下面加上这句话

```cmake
set(sub1_var ${sub1_var} PARENT_SCOPE)
```

相当于是：扩大了作用域，这时候，输出为：

```sh
[cmake] in func_sub1: sub1_var = 1
[cmake] in func_sub1: sub1_var = 2
[cmake] in sub1: sub1_var = 2
[cmake] ===========================
[cmake] in func_sub1: sub1_var = 3
[cmake] in main: sub1_var = 3
```

这个时候，是 sub1_var 是同一个内存

### include

如果是`include`子目录，而不是`add_subdirectory`，
结果是不一样的，因为`include`是直接将子目录复制过来了，
相当于就是：头文件展开的复制
