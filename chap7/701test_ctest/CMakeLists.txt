cmake_minimum_required(VERSION 3.22)
project(test_ctest)

file(WRITE test_ctest.cc [=[
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    if (argc <= 1) { // 没有传递参数
        return -1;
    } else {
        cout << argv[1] << endl;
        return 0;
    }
}
]=])

add_executable(${PROJECT_NAME} test_ctest.cc)

# 添加测试用例
add_test(
    NAME test_return-1 # 测试的名称，用于控制台输出显示
    COMMAND ${PROJECT_NAME}
)
add_test(
    NAME test_return0 # 测试的名称，用于控制台输出显示
    COMMAND ${PROJECT_NAME} 1
)

add_test(
    NAME test_success # 检测控制台输出
    COMMAND ${PROJECT_NAME} success
)

set_tests_properties(
    test_success
    PROPERTIES
    PASS_REGULAR_EXPRESSION success
)

add_test(
    NAME test_failed
    COMMAND ${PROJECT_NAME} failed
)

set_tests_properties(
    test_failed
    PROPERTIES
    FAIL_REGULAR_EXPRESSION fail
)
enable_testing()
