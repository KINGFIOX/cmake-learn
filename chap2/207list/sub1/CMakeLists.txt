# ./sub1/cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(sub1)

# 设置全局属性
set_property(
    GLOBAL
    PROPERTY TEST_sub1 # 属性名
    "test global sub 001"
)

# # 获取属性
# get_property(
# val
# GLOBAL
# PROPERTY TEST_GLOBAL
# )

# # 以及获取到了全局属性
# message("test global = ${val}")
message("===========================")

# 目录属性
set_property(
    DIRECTORY . # 当前路径，默认是当前路径（作用域）
    PROPERTY DIR2
    "dir002"
)
