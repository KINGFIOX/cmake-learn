# ./cmakelists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_env)

set(out "")

# 遍历：左闭右闭区间
foreach(var RANGE 5)
    # message("var = ${var}")
    string(APPEND out ${var} " ")
endforeach(var RANGE 5)

message("out = ${out}")

# 指定范围
foreach(var RANGE 1 9 2)
    message("var = ${var}")
endforeach(var)

set(arr1 "1;3;5;7;9")
set(arr2 "2;4;6;8;10")

foreach(num IN ZIP_LISTS arr1 arr2)
    message("num_0 = ${num_0}")
    message("num_1 = ${num_1}")
endforeach(num IN ZIP_LISTS arr1 arr2)

foreach(var RANGE 100)
    math(EXPR re "${var} %3")

    if(re EQUAL 0)
        message(${var})
        continue()
    endif()

    message(".")

    if(var GREATER 50)
        break()
    endif()
endforeach(var RANGE 100)

set(var 1)

while(var)
    math(EXPR var "${var} + 1")
    math(EXPR re "${var} % 10")

    if(re)
        continue()
    endif()

    message(${var})

    if(var GREATER 100)
        set(var 0)
    endif()
endwhile(var)
