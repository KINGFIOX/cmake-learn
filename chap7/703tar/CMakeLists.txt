cmake_minimum_required(VERSION 3.22)
project(gtest_tar)

file(WRITE "${PROJECT_NAME}.cc" [=[
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

// 添加一个测试
TEST(MyTest, MyTestDownload)
{
    EXPECT_EQ(7 * 6, 42); // 判断是否相等
}

TEST(MyTest, MyTestUpload)
{
    EXPECT_EQ(7 * 6, 41); // 判断是否相等
}

class XLogTest : public ::testing::Test {
protected:
    XLogTest()
    {
        cout << "Create XLogTest" << endl;
    }
    ~XLogTest()
    {
        cout << "Drop XLogTest" << endl;
    }
    void SetUp() override // 每次测试开始进入
    {
        cout << "SetUp XLogTest" << endl;
    }
    void TearDown() override
    {
        cout << "TearDown XLogTest" << endl;
    }
};
TEST_F(XLogTest, Init)
{
    ASSERT_TRUE(true);
}
TEST_F(XLogTest, Write)
{
    ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
    // 初始化gtest
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
]=])

set(GTEST_INSTALL ${CMAKE_SOURCE_DIR}/gtest)

# 如果没有安装才执行：解压，编译，安装
if(NOT EXISTS GTEST_INSTALL)
    execute_process(COMMAND ${CMAKE_COMMAND}
        -E tar xf ${CMAKE_SOURCE_DIR}/gtest-1.11.0.tar.gz
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    set(gtest ${PROJECT_BINARY_DIR}/googletest-release-1.11.0)
    execute_process(COMMAND
        ${CMAKE_COMMAND} -S ${gtest} -B ${gtest}/build
    )
    execute_process(COMMAND
        ${CMAKE_COMMAND} --build ${gtest}/build
    )
    execute_process(COMMAND
        ${CMAKE_COMMAND} --install ${gtest}/build --prefix=${GTEST_INSTALL}
    )
endif(NOT EXISTS GTEST_INSTALL)

# 生成我们自己的 exe
add_executable(${PROJECT_NAME} "${PROJECT_NAME}.cc")

# 查找gtest库
list(APPEND CMAKE_PREFIX_PATH "${GTEST_INSTALL}")
find_package(GTest)

message("GTest = ${GTest_FOUND}")

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC GTest::gtest_main
)

# 联合ctest和gtest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

enable_testing()