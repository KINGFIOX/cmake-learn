# 501cmake_install/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(install_file)

set(CMAKE_INSTALL_PREFIX out)

file(WRITE doc/index.html "")
file(WRITE doc/doc.html "")
file(WRITE doc/doc.cc "")
file(WRITE doc/doc.c "")

install(DIRECTORY doc TYPE DOC)

# 过滤，只复制 *.html 文件
install(DIRECTORY doc DESTINATION html_doc
    FILES_MATCHING PATTERN "*.html"
)

# 排除
install(DIRECTORY doc DESTINATION no_c
    PATTERN "*.c" EXCLUDE
)

#
install(DIRECTORY doc DESTINATION and
    FILES_MATCHING
    PATTERN "*.cc"
    PATTERN ".git" EXCLUDE
)
