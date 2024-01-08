cmake_minimum_required(VERSION 3.22)
project(gtest_fetch)

file(WRITE test_gtest.cc [=[
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

// 添加一个测试
TEST(MyTest, MyTestDownload)
{
    EXPECT_EQ(7*6, 42);  // 判断是否相等
}

TEST(MyTest, MyTestUpload)
{
    EXPECT_EQ(7*6, 41);  // 判断是否相等
}

int main(int argc, char* argv[])
{
    // 初始化gtest
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
]=])

# 要下载，需要引入头文件
include(FetchContent)

# 下载代码 git svn http
FetchContent_Declare(
    googletest
    GIT_REPOSITORY http://www.github.com/google/googletest.git # git下载
    GIT_TAG release-1.12.1 # 指定release版本呢
)

# 编译安装
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} test_gtest.cc)

# 设置gtest的库，头文件自动推导
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC GTest::gtest_main
)

# 联合ctest和gtest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# 打开才能运行ctest
enable_testing()