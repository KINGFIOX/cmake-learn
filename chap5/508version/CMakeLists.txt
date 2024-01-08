# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(export_package)

# 传入version
if(NOT version)
    set(version 1.0)
endif()

# 需求：用户会在编译的时候传入版本号
# cmake -S . -B build -Dversion1.1
set(CMAKE_INSTALL_PREFIX "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5/slib-${version}")

# ####### 第一个库 #########
file(WRITE include/slib.h "void SLib();")
file(WRITE slib.cc.in [=[
#include <iostream>
#include "slib.h"  
void SLib(){
    std::cout << "${version} In SLib function!\n";
}
]=])

# 配置version（替换文件中的version）
configure_file("slib.cc.in" "${CMAKE_SOURCE_DIR}/slib.cc")

add_library(slib STATIC slib.cc)
set_target_properties(slib PROPERTIES PUBLIC_HEADER include/slib.h)

target_include_directories(slib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${version}/include>
    $<INSTALL_INTERFACE:${version}/include>
)

# ####### 生成 <PackageName>Config.cmake ############
install(TARGETS slib
    EXPORT slib # 要标注导出
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include # 记得导出头文件路径
)

install(EXPORT slib
    FILE slibConfig.cmake
    DESTINATION config
)
