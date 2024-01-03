# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_macro)

function(func1 arg1 arg2)
    message("IN function func1")
    message("arg1 = ${arg1}")
    message("arg2 = ${arg2}")

    if(arg1)
        message("arg1 == TRUE")
    else()
        message("arg1 != FALSE")
    endif()

    foreach(var IN LISTS arg1)
        message("var = ${var}")
    endforeach(var IN LISTS arg1)
endfunction(func1 arg1 arg2)

func1("1;2;3;4;5" 2)

message("===========================")

function(func_var arg1)
    message("in func_var ${arg1}")
    message("var1 = ${var1}")
    set(var1 "func var")
endfunction(func_var arg1)

set(var1 "main1")
set(arg1 "main arg1")
func_var(123)
message("var1 = ${var1}")

message("===========================")

add_subdirectory("./sub1")

message("===========================")

# 相当与是：这里有一个main_sub1_var，内存空间不一致
func_sub1()
message("in main: sub1_var = ${sub1_var}")
