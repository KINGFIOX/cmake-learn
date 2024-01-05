# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_object)

# a.cc b.cc => a.cc.o b.cc.o
# a.cc.o b.cc.o => testa
# main.cc libtesta.so => main
file(WRITE a.cc [=[
#include <iostream>
void A() {
    std::cout << "A\n";
}
]=])

file(WRITE b.cc [=[
#include <iostream>
void A() {
    std::cout << "B\n";
}
]=])

file(WRITE main.cc [=[
#include <iostream>
int main(void){
    A();
    B();
    std::cout << "in main" << std::endl;
}
]=])

# 添加object对象
add_library(
    testa_obj
    OBJECT
    a.cc b.cc
)

# target_compile_options(testa_obj PUBLIC "-fPIC")
set_target_properties(testa_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

# obj => so
# add_library(
# testa
# testa_obj
# )

# 用生成器表达式获取object对象
add_library(
    testa
    SHARED
    $<TARGET_OBJECTS:testa_obj>
)

# 这里会有错误，说我们没有加-fPIC

# # 生成静态库
# add_library(
# testa
# STATIC
# # $<TARGET_OBJECTS:testa_obj>
# testa_obj
# )
