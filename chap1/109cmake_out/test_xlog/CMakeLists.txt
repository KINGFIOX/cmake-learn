# CMakeLists.txt

# 最低版本
cmake_minimum_required(VERSION 3.20)

project(test_xlog)

# 添加头文件路径，相当于是-i，../xlog 下有 xlog.h文件
include_directories("../xlog")

# 指定库查找路径，到那边去找。以当前cmakelists.txt的相对路径
link_directories("../xlog/build")

add_executable(test_xlog test_xlog.cc)

# 制定加载的库，找哪一个库
# 这个xlog库不用libxlog.a，只用原本的名字即可
# 注意一下，需要是生成可执行文件之后指定库
# 毕竟编译顺序是：先生成a.o，再链接的。还得看那本书《程序员的自我修养》
target_link_libraries(test_xlog xlog)
