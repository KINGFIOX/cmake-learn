# CMakeLists.txt

# 先要限定最低版本
cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(xlog)

# 添加库，添加库的时候，不用xlog.o之类的，编译器会补充
add_library(xlog STATIC xlog.cc xlog.h)