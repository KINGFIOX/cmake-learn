# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(install_code)

set(CMAKE_INSTALL_PREFIX out)

file(WRITE "a.cc" "")
file(WRITE "doc.html" "")

install(FILES a.cc
    DESTINATION src
    COMPONENT src # 定义我们自己的 主键 名称
)

install(FILES doc.html
    DESTINATION doc
    COMPONENT doc
)