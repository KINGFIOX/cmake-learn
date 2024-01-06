# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_install)

# ############################################
# ## 1 静态库 导出 .lib .a

# 公开头文件
file(WRITE include/slib.h "void SLib();")

# 私有头文件
file(WRITE include/slib_pri.h "#define PRI")

file(WRITE slib.cpp "void SLib(){}")
add_library(slib STATIC slib.cpp include/slib.h include/slib_pri.h)

set_target_properties(slib PROPERTIES PUBLIC_HEADER include/slib.h)
set_target_properties(slib PROPERTIES PRIVATE_HEADER include/slib_pri.h)

# ###########################################################
# 2 动态库 需要dllexport导出，不然windows不生产.lib文件
# windows .lib .dll
# linux .so
# mac .dylib
file(WRITE include/dlib.h [=[
#ifdef _WIN32
__declspec(dllexport)
#endif
void DLib();
]=])

file(WRITE dlib.cpp [=[
#include "dlib.h"
void DLib(){}
]=])
add_library(dlib SHARED dlib.cpp include/dlib.h)
target_include_directories(dlib PUBLIC include)

# #################################################
# 3 执行程序 引用动态库和静态库
file(WRITE main.cpp [=[
#include "dlib.h"
#include "slib.h"
int main()
{
    DLib();
    SLib();
    return 0;
}
]=])
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} dlib)
target_link_libraries(${PROJECT_NAME} slib)
target_include_directories(${PROJECT_NAME} PUBLIC include)

# ######################################

# ###### 安装目标 ########
set(CMAKE_INSTALL_PREFIX ./out)

# 安装目标 desination 指定 相对 cmake_install_prefix 的输出路径
# cmake_install_prefix默认是/usr/local
# 可以在生成的时候 cmake -S . -B build -DCMAKE_INSTALL_PREFIX=<path>
# install(TARGETS slib dlib ${PROJECT_NAME} DESTINATION bin)

# cmake --install build（这个和build平行的）
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin # 执行程序
)

install(TARGETS slib dlib
    CONFIGURATIONS Release
    RUNTIME DESTINATION bin # 执行程序和dll文件输出
    ARCHIVE DESTINATION lib # 静态库和windows动态库导出符号.lib
    LIBRARY DESTINATION lib # linux和mac的动态库.so 和 .lib导出到lib种
    PRIVATE_HEADER DESTINATION include
    PUBLIC_HEADER DESTINATION inc
)

install(TARGETS slib dlib
    CONFIGURATIONS Debug
    RUNTIME DESTINATION debug/bin # 执行程序和dll文件输出
    ARCHIVE DESTINATION debug/lib # 静态库和windows动态库导出符号.lib
    LIBRARY DESTINATION debug/lib # linux和mac的动态库.so 和 .lib导出到lib种
    PRIVATE_HEADER DESTINATION debug/include
    PUBLIC_HEADER DESTINATION debug/inc
)