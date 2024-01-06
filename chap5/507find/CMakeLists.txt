# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.26)
project(findpkg)

list(APPEND CMAKE_PREFIX_PATH "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5/slib")

set(slib_DIR "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5/slib/config")
list(APPEND slib_INCLUDE_DIRS "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap5/slib/include")

# set(CMAKE_INSTALL_PREFIX out)
file(WRITE main.cc [=[
#include "slib.h"
#include <iostream>
using namespace std;
int main(void){
    cout << "in main" << endl;
    SLib();
    return 0;
}
]=])

find_package(slib)
message("slib_FOUND = ${slib_FOUND}")

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} slib)
target_include_directories(${PROJECT_NAME} PRIVATE ${slib_INCLUDE_DIRS})
message("slib_INCLUDE_DIRS = ${slib_INCLUDE_DIRS}")