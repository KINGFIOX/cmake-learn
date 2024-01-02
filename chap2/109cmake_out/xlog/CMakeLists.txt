# 106cmake_system/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(xlog)

# 2. 改变行为的变量
# 注意一下，这个BUILD_SHARED_LIBS是 缓存变量
set(BUILD_SHARED_LIBS ON)

# 3. 描述系统的变量
message("MSVC=" ${MSVC})
message("UNIX=" ${UNIX})

# 4. 控制构建过程的变量：输出路径控制
# CMAKE_COLOR_MAKEFILE是否生成makefile的颜色，默认是ON
set(CMAKE_COLOR_MAKEFILE OFF)

# 传递变量给C++，静态库
add_definitions(-Dxlog_STATIC)

# 1. 提供信息的变量
add_library(${PROJECT_NAME} ./xlog.h ./xlog.cc)
