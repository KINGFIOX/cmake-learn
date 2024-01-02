cmake_minimum_required(VERSION 3.20)

message("参数1")
message("参数p1" "参数p2" "p3" 123 测试)

# 查找

# 开始查找
message(CHECK_START "find xcpp")

# 查找库代码
# ...

# 结束查找 查找失败
message(CHECK_FAIL "not found")