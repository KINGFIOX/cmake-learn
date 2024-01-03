# 201cmake_if/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

project(test)

set(VAR_DEF OFF)

if(DEFINED VAR_DEF)
    message("is defined")
endif()

if(DEFINED VAR_NOT_DEF)
    message("is defined")
else()
    message("is not defined")
endif()

if("abcd123" MATCHES "^[a-z]+$")
    message("is match")
else()
    message("is not match")
endif()
