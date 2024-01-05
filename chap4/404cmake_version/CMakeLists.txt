# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_object)

file(WRITE a.cc [=[
void A(){}
]=])

file(WRITE main.cc [=[
int main(void){return 0}
]=])

add_library(a SHARED ./a.cc)

set_target_properties(
    a
    PROPERTIES
    VERSION "2.0.1"
    SOVERSION "15"
)

#[[ 依赖顺序：liba.dylib --> liba.15.dylib --> liba.2.0.1.dylib
lrwxr-xr-x  1 wangfiox  staff    16B Jan  5 19:24 liba.15.dylib -> liba.2.0.1.dylib
-rwxr-xr-x  1 wangfiox  staff    17K Jan  5 19:24 liba.2.0.1.dylib
lrwxr-xr-x  1 wangfiox  staff    13B Jan  5 19:24 liba.dylib -> liba.15.dylib
]]