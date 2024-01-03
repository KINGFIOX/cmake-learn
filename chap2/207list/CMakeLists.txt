# ./cmakelists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_env)

set(src "a" "b" "c" "d;e")
message("src = ${src}") # a;b;c;d;e
list(LENGTH src len)
message("src length = ${len}")

# list追加
list(APPEND src "g")
list(APPEND src "h;i")
message("src = ${src}")
list(LENGTH src len)
message("src length = ${len}")

# list访问 下标访问：0 1 2 3 ... -1 -2 -3 ...
list(GET src 1 var)
message("GET src 1 = ${var}")
list(GET src -1 var)
message("GET src -1 = ${var}")

list(JOIN src "|" var)
message("JOIN src = ${var}")

list(SUBLIST src 0 3 var)
message("SUBLIST ${var}")

list(FIND src "d" var)
message("FIND ${var}")

# 插入节点 a;b;c;d;e;f;g;h;i
list(INSERT src 4 "d1")
list(INSERT src 2 "b1")
message("insert src ${src}")

# [cmake] insert src a;b;b1;c;d;d1;e;g;h;i
list(REMOVE_ITEM src "b")
message("remove src = ${src}")

# 后端出队
list(POP_BACK src var)
message("pop_back ${var}")
message("pop_back ${src}")

# 去重
set(rsrc "1;2;3;3;2;1;1;2;3;4;5;6;7")
message("rsrc before = ${rsrc}")
list(REMOVE_DUPLICATES rsrc)
message("rsrc after = ${rsrc}")

set(arr "8;12;5;7;9;3")
list(SORT arr)
message("arr = ${arr}")

# 自然数排序
list(SORT arr COMPARE NATURAL)
message("arr = ${arr}")
