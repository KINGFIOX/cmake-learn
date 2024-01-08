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
