# 107cmake_include/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

project("cmake_include")
message("begin include")

# include
include("./cmake/test_cmake.cmake")

include("./cmake/test_cmake.cmake" OPTIONAL) # 文件不存在不报错
include("./cmake/test_cmake.cmake" OPTIONAL RESULT_VARIABLE ret) # 看看引用是否成功
message("RET = ${ret}")

message("end include")