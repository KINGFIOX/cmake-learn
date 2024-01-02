# 110add_subdirectory/cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(xlog)
include_directories("./xlog")

# 静态库，动态库的配置放到外面来做
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")
set(BUILD_SHARED_LIBS ON)

add_subdirectory("./xlog")
add_subdirectory("./test_xlog")
