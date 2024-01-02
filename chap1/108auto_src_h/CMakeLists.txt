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
