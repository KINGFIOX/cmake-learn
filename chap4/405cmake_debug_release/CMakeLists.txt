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

# 静态库 输出路径
add_library(slib STATIC src/slib.cc)
set(OUT_LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(slib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_LIB_PATH} # 静态库和lib文件的输出
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUT_LIB_PATH}/debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_LIB_PATH}/release
)

# 默认是debug
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# 动态库
file(WRITE include/dlib.h [=[
#ifndef _WIN32  // unix
    #define XCPP_API
#else  // windows
    #ifdef xlog_EXPORTS
        #define XCPP_API __declspec(dllexport)
    #else
        #define XCPP_API __declspec(dllimport)
    #endif
#endif
XCPP_API void DLib();
]=])

file(WRITE src/dlib.cc [=[
#include "dlib.h"
void DLib() { }
]=])

add_library(
    dlib
    SHARED
    src/dlib.cc
    include/dlib.h
)

target_include_directories(
    dlib PUBLIC ./include
)

set(OUT_EXE_PATH ${CMAKE_SOURCE_DIR}/bin)

# windows lib文件输出
set_target_properties(dlib PROPERTIES

    # windows lib
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_LIB_PATH}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUT_LIB_PATH}/debug
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_LIB_PATH}/release

    # windows dll
    RUNTIME_OUTPUT_DIRECTORY ${OUT_EXE_PATH}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUT_EXE_PATH}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_EXE_PATH}/release

    # linux .so 和 mac
    LIBRARY_OUTPUT_DIRECTORY ${OUT_EXE_PATH}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUT_EXE_PATH}/debug
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUT_EXE_PATH}/release
)

file(WRITE src/main.cc [=[

#include "dlib.h"

void SLib();
int main() {
    DLib();
    SLib();
    return 0;
}
]=])

add_executable(main src/main.cc)
target_link_libraries(main slib dlib)

# windows lib文件输出
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUT_EXE_PATH}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUT_EXE_PATH}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_EXE_PATH}/release
    DEBUG_POSTFIX "d" # debug版本添加后缀
)