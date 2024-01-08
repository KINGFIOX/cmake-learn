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
