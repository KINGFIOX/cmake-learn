# 109cmake_out/cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(xlog)

# 头文件搜索路径
include_directories("./xlog")

# cmakelists.txt路径
message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# 动态库 输出路径，但是这里却是在./build/lib这个目录下生成
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")

# 可执行程序 输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

# 生成动态库
add_library(xlog SHARED xlog/xlog.cc)

# 生成可执行文件
add_executable(test_xlog ./test_xlog/test_xlog.cc)

# 链接库
target_link_libraries(test_xlog xlog)
