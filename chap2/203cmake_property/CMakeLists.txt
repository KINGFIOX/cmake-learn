# ./cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_property)

# 设置全局属性
set_property(
    GLOBAL
    PROPERTY TEST_GLOBAL # 属性名
    "test global 001"
)

# 获取属性
get_property(
    val
    GLOBAL
    PROPERTY TEST_GLOBAL
)

# 以及获取到了全局属性
message("test global = ${val}")

# 添加子目录
add_subdirectory("./sub1")

# 获取子目录的全局属性
get_property(
    val_sub1
    GLOBAL
    PROPERTY TEST_sub1
)

message("test sub1 = ${val_sub1}")

message("===========================")

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
message("test_append = ${val2}") # append001;append 002

message("===========================")

# get_property set | defiend
set_property(
    GLOBAL
    PROPERTY p1
    "p1"
)
get_property(
    var3
    GLOBAL
    PROPERTY p1
    SET # 是否被设置
)
message("p1 = ${var3}")

message("===========================")

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

# 获取描述
get_property(
    doc
    GLOBAL
    PROPERTY test_def
    BRIEF_DOCS
)
message("p1 = ${doc}")

message("===========================")

# 目录属性
set_property(
    DIRECTORY . # 当前路径，默认是当前路径（作用域）
    PROPERTY DIR1
    "dir001"
)
get_property(
    var5
    DIRECTORY .
    PROPERTY
    DIR1
)
message("var5 = ${var5}")

get_property(
    var6
    DIRECTORY .
    PROPERTY
    DIR2
)
message("dir2 = ${var6}")

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

message("===========================")

# cmake 目标属性，要求目标已经存在
set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY TVAR "tval"
)
get_property(
    var8
    TARGET ${PROJECT_NAME}
    PROPERTY TVAR
)
message("var8 = ${var8}")

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

# 打印属性
include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS ${PROJECT_NAME}
    PROPERTIES
    COMPILE_DEFINITIONS
    TVAR
)
