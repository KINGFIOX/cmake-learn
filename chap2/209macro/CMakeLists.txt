# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_macro)

macro(my_macro)
    message("in my macro")
endmacro(my_macro)

# 两种调用方式
my_macro()
cmake_language(CALL my_macro)

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

message("===========================")

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
    TARGETS "ta1" "ta2" "ta3"
)

message("===========================")

my_parse(
    LOG "mylog"
    BIN "mybin"
    TARGETS "ta1" "ta2" "ta3"
)

message("===========================")

my_parse(
    LOG
    BIN "mybin"
    LIB # 需要传一个值，但是没有
    TARGETS "ta1" "ta2" "ta3"
)

# my_parse(1 2 3 3 2 1 1 2 3 4 5 6 7)
