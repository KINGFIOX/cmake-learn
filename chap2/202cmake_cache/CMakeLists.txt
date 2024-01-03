# ./cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_cache)

message("in main")

# 设置缓存变量的类型，对应于string类型
set(var1 "CACHE var1 value" CACHE STRING "cache doc")

set(var1 "CACHE var1 value1-1" CACHE STRING "cache doc")
set(var1 "CACHE var1 value1-2" CACHE STRING "cache doc" FORCE)

message("var1 = ${var1}")

set(VAR_NORMAL "test normal")
message("var_normal =  ${VAR_NORMAL}")

add_subdirectory("./sub1") # 子目录会获取当前普通变量
add_subdirectory("./sub2")

message("in main var_sub1 = ${var_sub1}") # 获取不到 sub1 的 普通变量
message("in main var_cache_sub1 = ${var_cache_sub1}")

message("----------------------------")

# 设置缓存变量 覆盖 同名普通变量 的策略
cmake_policy(SET CMP0126 NEW)

# 普通变量
set(NVAR1 "normal var1")

# cache变量
set(NVAR1 "cache var1" CACHE STRING "cache doc")

message("NVAR1 = ${NVAR1}")
message("NVAR1 = $CACHE{NVAR1}")

# 用户传递的变量
message("para1 = ${PARA1}")