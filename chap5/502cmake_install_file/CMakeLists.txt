# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(install_file)

file(WRITE a.h "")
file(WRITE b.h "")
file(WRITE c.h "")

set(CMAKE_INSTALL_PREFIX ./out)

# 文件安装到指定目录
install(FILES a.h b.h
    DESTINATION include
)

install(FILES c.h
    DESTINATION inc OPTIONAL
)

include(GNUInstallDirs)
message("CMAKE_INSTALL_DATAROOTDIR = ${CMAKE_INSTALL_DATAROOTDIR}") # 默认是share
install(FILES a.h TYPE DOC) # <DATAROOT dir>/doc
install(FILES b.h TYPE LIB) # /lib

# 文件权限
install(FILES a.h
    DESTINATION pub
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ
)
