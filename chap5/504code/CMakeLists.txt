# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(install_code)

set(CMAKE_INSTALL_PREFIX out)

file(WRITE a.h "")
file(WRITE b.h "")
install(CODE "message(\"begin install\")")

install(FILES a.h TYPE INCLUDE)
install(CODE "message(\"a.h install success!\")")
install(FILES b.h TYPE INCLUDE)
install(CODE "message(\"b.h install success!\")")

install(CODE [=[
    string(TIMESTAMP now "%Y-%m-%d %H:%M:%S")
    message(${now})
    FILE(APPEND install_log.txt "${now}\n")
]=])
