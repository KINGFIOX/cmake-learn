# CMakeLists.txt

# 指定最低版本
cmake_minimum_required(VERSION 3.20)

project(xlog)

# 头文件，这个头文件路径是一个全局的，xlog可以看见，test_xlog也可以看见
include_directories("./xlog")

# 生成动态库
add_library(xlog SHARED ./xlog/xlog.cc ./xlog/xlog.h)

# 生成可执行文件
add_executable(test_xlog ./test_xlog/test_xlog.cc)

# 链接
target_link_libraries(test_xlog xlog)
