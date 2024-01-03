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

set(sub1_var ${sub1_var} PARENT_SCOPE)
