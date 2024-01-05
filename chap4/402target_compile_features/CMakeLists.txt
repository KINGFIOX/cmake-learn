# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_target_include)

file(WRITE main.cc [=[
int main(void){
    return 0;
}
]=])

add_executable(main main.cc)

# 支持 C++17
target_compile_features(main PRIVATE cxx_std_17)

# message("CMAKE_CXX_COMPILE_FEATURES = ${CMAKE_CXX_COMPILE_FEATURES}")
set(f1 cxx_std_23)

if(f1 IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message("use cxx_std_23")
endif()