cmake_minimum_required(VERSION 3.20)
project(message_color)

#[[
\033[1;31;40m  --> 1 高亮显示 ; 31 前景色红色 ; 40 背景色红色
\033[0m  --> 0m 表示，取消颜色设置

这里的\033是8进制ascii（c语言考过）

上面这两条是配对的
]]
string(ASCII 27 Esc)

set(R "${Esc}[0;31m")
set(E "${Esc}[0m")

message("${R}红色内容${E} 默认颜色")
message("${R}蓝色内容${E} 默认颜色")