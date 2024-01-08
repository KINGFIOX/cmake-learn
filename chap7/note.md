# chap7 - cmake 自动单元测试

有两种单元测试：ctest(cmake 内置)、gtest（google test）

## ctest

### add_test

```cmake
add_test(NAME <name> COMMAND <command> [<arg>...]
         [CONFIGURATIONS <config>...]
         [WORKING_DIRECTORY <dir>]
         [COMMAND_EXPAND_LISTS])
```

或者是也可以是：生成表达式

```cmake
add_test(NAME mytest
         COMMAND testDriver --config $<CONFIG>
                            --exe $<TARGET_FILE:myexe>)
```

### enable_testing()

### 成功失败判断方法

有时候期望成功、有时候期望失败

#### main 函数返回值

#### PASS_REGULAR_EXPRESSION

成功输出的正则表达式（这个需要打印一些调试信息）

#### fail_regular_expression

检查哪些是失败的

### 编译步骤

### 示例 1 - 常规的 add_test - 检测返回值

#### 编写 cmake

```cmake
cmake_minimum_required(VERSION 3.22)
project(test_ctest)

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

enable_testing()
```

1. 添加测试用力
2. 开启测试

就是这个`add_test`，是用来检测返回值的

#### 进入到 build 目录，然后 ctest

```sh
~/DOCs/cpp/cmakeLearn/notes/chap7/701test_ctest/build (main*) » ctest -C Debug
Test project /Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap7/701test_ctest/build
    Start 1: test_return-1
1/2 Test #1: test_return-1 ....................***Failed    0.00 sec
    Start 2: test_return0
2/2 Test #2: test_return0 .....................   Passed    0.00 sec

50% tests passed, 1 tests failed out of 2

Total Test time (real) =   0.01 sec

The following tests FAILED:
          1 - test_return-1 (Failed)
Errors while running CTest
Output from these tests are in: /Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap7/701test_ctest/build/Testing/Temporary/LastTest.log
Use "--rerun-failed --output-on-failure" to re-run the failed cases verbosely.
```

`-C`表示指定版本，我们这里指定成了 Debug 版本

### 示例 2 - 使用 set_tests_properities - 检测打印信息

```cmake
add_test(
    NAME test_failed
    COMMAND ${PROJECT_NAME} "failed"
)

set_tests_properties(
    test_failed
    PROPERTIES
    FAIL_REGULAR_EXPRESSION fail
)
```

这段代码的意思是：

如果这个`{PROJECT_NAME}`可执行程序中，有打印`fail`之类的字样，
那么就会失败，也就是`set_test_properties`的效果。

这里传入参数`failed`也确实打印了"fail"之类的字样，
所以这段测试程序，这里并没有通过。

## gtest

### 安装方法

- git 源码下载编译（可能失败，懂得都懂）

```cmake
# 要下载，需要引入头文件
include(FetchContent)

# 下载代码 git svn http
FetchCOntent_Declare(
    googletest
    GIT_REPOSITORY http://www.github.com/google/googletest.git # git下载
    GIT_TAG release-1.12.1 # 指定release版本呢
)

# 编译安装
FetchCOntent_MakeAvailable(googletest)
```

- http 直接下载发布库和头文件

```cmake
# http下载
FetchContent_Declare(
    googletest
    URL http://cdn.tarsyun.com/src/release-1.11.0.tar.gz
)
```

- 手动下载源码编译安装

`cmake -S . -B build`后，就可以看到，在 `build/_deps` 中就有我们的 googletest

然后我们`cmake --build build`以后，就可以在`build/lib`中看到一些静态库`libgtest.a`等

当然，还可以进行安装`cmake --install build --prefix=./`（安装到当前路径），
然后就可以使用 find_package 了

### 示例 1 - gtest 使用

```c
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

// 添加一个测试
TEST(MyTest, MyTestDownload)
{
    EXPECT_EQ(7*6, 42);  // 判断是否相等
}

// 再添加一个测试用例，这里就变成了upload
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
```

#### ctest 和 gtest 联合使用

主要是使用 gtest 需要 ctest 的配合，所以要`enable_testing()`

```cmake
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
```

这里用到了链接库`target_link_libraries`，这个库很好，
会帮我们自动推导头文件路径

### execute_process

```cmake
# 执行一个进程
execute_process(COMMAND <cmd1> [<arguments>]
                [COMMAND <cmd2> [<arguments>]]...
                [WORKING_DIRECTORY <directory>]
                [TIMEOUT <seconds>]
                [RESULT_VARIABLE <variable>]
                [RESULTS_VARIABLE <variable>]
                [OUTPUT_VARIABLE <variable>]
                [ERROR_VARIABLE <variable>]
                [INPUT_FILE <file>]
                [OUTPUT_FILE <file>]
                [ERROR_FILE <file>]
                [OUTPUT_QUIET]
                [ERROR_QUIET]
                [COMMAND_ECHO <where>]
                [OUTPUT_STRIP_TRAILING_WHITESPACE]
                [ERROR_STRIP_TRAILING_WHITESPACE]
                [ENCODING <name>]
                [ECHO_OUTPUT_VARIABLE]
                [ECHO_ERROR_VARIABLE]
                [COMMAND_ERROR_IS_FATAL <ANY|LAST>])
```

###
