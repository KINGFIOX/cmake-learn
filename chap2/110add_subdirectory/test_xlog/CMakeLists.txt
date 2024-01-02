# CMakeLists.txt

# 最低版本
cmake_minimum_required(VERSION 3.20)

project(test_xlog)

add_executable(test_xlog test_xlog.cc)

target_link_libraries(test_xlog xlog)
