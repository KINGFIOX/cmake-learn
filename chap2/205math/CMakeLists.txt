# ./cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_env)

# 环境变量使用
set(ENV{MYENV} "test env value")
message("MYENV = $ENV{MYENV}")

message("username = $ENV{USER}")

set(expr "(2*10) + 5")
math(EXPR out ${expr} OUTPUT_FORMAT HEXADECIMAL)
message("out = ${out}")
