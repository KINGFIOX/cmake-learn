# ./cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_env)

# 需求：取出begin和end之间的内容
set(STR1 "xxx begin test cmake string end xxxxxx")

# 查找开头字符串
set(BSTR "begin")

# 在 str1 中，查找 bstr 位置，存入b
string(FIND ${STR1} ${BSTR} b)

message("FIND ${BSTR} pos ${b}")

string(FIND ${STR1} "end" e)
message("FIND end pos ${e}")

# 去掉begin字符位置
# 获取字符串长度
string(LENGTH ${BSTR} size)
math(EXPR b "${b}+${size}")
message("b = ${b}")

math(EXPR length "${e}-${b}")
message("length = ${length}")

# 获取子串
string(SUBSTRING ${STR1} ${b} ${length} substr)
message("substr = [${substr}]")

# 去掉空格
string(STRIP ${substr} substr)
message("substr = [${substr}]")

# 转成大写
string(TOUPPER ${substr} substr)
message("substr = [${substr}]")

# 追加
string(APPEND substr "append01" "append02")
message("substr = [${substr}]")

# 替换
string(REPLACE "append" "REPLACE" substr ${substr})
message("substr = [${substr}]")

string(REGEX MATCH "[A-Z]+[0-9]+" output ${substr})
message("regex output = [${output}]")

set(
    tjson
    [=[
        {
            "webs" : {
                "web" : [
                    {"name": "cmake", "url":"cmake.org.cn"},
                    {"name": "ffmpeg", "url":"ffmpeg.club"}
                ]
            }   
        }
    ]=]
)
message(${tjson})

# 访问webs.web[0].name
string(JSON var ERROR_VARIABLE evar GET ${tjson} webs web 0 name)
message("var = ${var}")
message("evar = ${evar}")

# 读取json数组长度
string(
    JSON
    web_count
    ERROR_VARIABLE evar
    LENGTH
    ${tjson} webs web
)
message("JSON LENGTH = ${web_count}")

string(
    JSON
    modified_json
    ERROR_VARIABLE evar
    SET
    ${tjson} webs web 2 [=[
        {"name":"cpp", "url":"cppreference.com"}
    ]=]
)
message("modified_json = ${modified_json}")

string(
    JSON
    remove_json
    ERROR_VARIABLE evar
    REMOVE
    ${tjson} webs web 1
)
message("removed_json = ${remove_json}")