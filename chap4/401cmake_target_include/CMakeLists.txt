# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_target_include)

# write 写文件，清空原数据，相当于fopen
# 直接创建代码
file(WRITE a.cc [=[
#include <iostream>
using namespace std;
void A(){
    #ifdef A_VAR
    cout << "in A " << A_VAR << endl;
    #endif
}
]=])

# cmake原生属性调试接口
set(CMAKE_DEBUG_TARGET_PROPERTIES INCLUDE_DIRECTORIES INTERFACE_INCLUDE_DIRECTORIES)

# 创建 静态库
add_library(A STATIC ./a.cc)

#[[
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
]]
target_include_directories(A PUBLIC "./A_PUBLIC")

target_compile_definitions(A PUBLIC A_VAR=123)

# 打印A的属性
include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS A
    PROPERTIES
    INCLUDE_DIRECTORIES
    INTERFACE_INCLUDE_DIRECTORIES
)

# B -> A
file(WRITE b.cc [=[
#include <iostream>
using namespace std;
void A();
void B(){
    A();
    #ifdef A_VAR
    cout << "in B: A_VAR=" << A_VAR << endl;
    #endif
}
]=])

add_library(B STATIC b.cc)
target_link_libraries(B PUBLIC A)
target_include_directories(B PUBLIC A) # 这样 main 也能获得 A 的属性

# 设定 B 库的宏：STATIC=1。B库编译时不需要; 依赖B库时需要（也就是interface0
target_compile_definitions(B INTERFACE STATIC=1)

# 打印B的属性
include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS B
    PROPERTIES
    INCLUDE_DIRECTORIES
    INTERFACE_INCLUDE_DIRECTORIES
)

file(WRITE main.cc [=[
#include <iostream>
using namespace std;
int main(void) {
    void B ();  // 这里是我们自己做了一个声明，现在是找不到定义
    B();
    #ifdef STATIC
    cout << "in main: STATIC=" << STATIC << endl;
    #endif
    return 0;
}
]=])

add_executable(main main.cc)

target_link_libraries(main PUBLIC B)

include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS main
    PROPERTIES
    INCLUDE_DIRECTORIES
    INTERFACE_INCLUDE_DIRECTORIES
)
