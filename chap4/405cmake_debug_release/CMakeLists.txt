# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_object)

# 静态库
# src/
# ----- slib.cc
# ----- dlib.cc
# ----- main.cc
# bin/
# ----- debug
# --------- main
# --------- dlib.dll [windows]
# ----- release
# --------- ...
# lib/
# ----- debug
# --------- slib.lib [windows]
# --------- dlib.lib [windows]
# --------- dlib.so
# --------- dlib.a
# ----- release
# --------- ...
file(WRITE src/slib.cc [=[
void SLib(){

}
]=])

add_library(slib STATIC src/slib.cc)

# 输出路径
set(OUT_LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(slib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_LIB_PATH} # 静态库和lib文件的输出
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUT_LIB_PATH}/debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_LIB_PATH}/release
)

# 默认是debug
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
