# ./CMakeLists.txt

cmake_minimum_required(VERSION 3.21)
project(expr)

add_executable(${PROJECT_NAME} expr.cc)

#[[
    1. 逻辑运算符
    "$<BOOL:OFF>" --> 0

    2. 条件表达式
    $<condition:true_string> 0返回空串; 1 返回 true_string
    "$<$<BOOL:OFF>:TEST1=123>" --> 这样的话，TEST1=(none)

]]
# 为目标的编译增加一些 宏变量
target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC # 后面再说，这个和依赖有关系
    "$<$<BOOL:ON>:TEST1=123>"
)

set(LIB OFF)

message($< $< NOT:$< BOOL:${LIB}> >:STATIC >)

# 利用cmake的错误来查看  --> cmake error in cmakelists.txt
# target_include_directories( ${PROJECT_NAME} PUBLIC "$<AND:1,0>")
# target_include_directories(${PROJECT_NAME} PUBLIC "$<OR:1,0>")
# add_custom_target(
# gen
# COMMAND ${CMAKE_COMMAND} -E echo "$<$<NOT:$<BOOL:${LIB}>>:STATIC=1>"
# )
message(${CMAKE_SYSTEM_NAME})

# target_include_directories(
# ${PROJECT_NAME}
# PUBLIC
# "$<CONFIG>"
# )
# target_include_directories(
# ${PROJECT_NAME}
# PUBLIC
# "$<PLATFORM_ID: Darwin>"
# )
set(LIB ON)

# target_include_directories(
# ${PROJECT_NAME}
# PUBLIC
# "$<IF:$<BOOL:${LIB}>, fuck, you>"
# )

# target_include_directories(
# ${PROJECT_NAME}
# PUBLIC
# "$<$<BOOL:ON>:${e}>"
# )
set(var $<TARGET_FILE:expr>)
add_custom_target(
    gen
    COMMAND ${CMAKE_COMMAND} -E echo "${var}"
)
