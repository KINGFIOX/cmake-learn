# ./sub1/cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(sub1)

message("in sub2")

message("in sub1 var_normal = ${VAR_NORMAL}")

set(var_sub1 "sub1 value")
message("in sub1 var_sub1 = ${var_sub1}")

# 定义 cache 变量
set(var_cache_sub1 "var cache sub1 value" CACHE STRING "sub1 doc")
message("in sub1 var_cache_sub1 = ${var_cache_sub1}")
