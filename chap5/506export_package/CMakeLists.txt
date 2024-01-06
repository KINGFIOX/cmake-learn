# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(export_package)

set(CMAKE_INSTALL_PREFIX "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5")

# ####### 第一个库 #########
file(WRITE include/slib.h "void SLib();") # 需要头文件，因为需要别人调用的时候引导
file(WRITE slib.cc [=[
#include <iostream>
#include "slib.h"  // 头文件引用问题
void SLib(){
std::cout << "In SLib function!\n";
}
]=])
add_library(slib STATIC slib.cc)
set_target_properties(slib PROPERTIES PUBLIC_HEADER include/slib.h)

# target_include_directories(slib PUBLIC include) # 注意一下这个public，这个涉及到别人引用的时候的问题
target_include_directories(slib PUBLIC # 路径两次被引用：1.编译slib库时; 2. export写入config时
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # 只有编译的时候有效
    $<INSTALL_INTERFACE:include> # 只有install的时候有效
)

#[[
CMake Error in CMakeLists.txt:
Target "slib" INTERFACE_INCLUDE_DIRECTORIES property contains path:

"/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5/506export_package/include"

which is prefixed in the source directory.

target_include_directories 的 public 会产生两个路径，一个是 include_dir，一个是 interface_dir。
就是我们在导出slibConfig.cmake的时候，会写入库路径，头文件路径
]]

# ######## 安装库 #########
# install(TARGETS slib

# RUNTIME DESTINATION bin
# LIBRARY DESTINATION lib
# ARCHIVE DESTINATION lib
# )

# ####### 生成 <PackageName>Config.cmake ############
# 我们接下来，将slibConfig.cmake放到./out/lib/config中
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
