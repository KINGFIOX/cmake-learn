# chap8 - cmake 构建项目

## 目录

```sh
(base) -------
~/DOCs/cpp/cmakeLearn/notes/chap8/project (main*) » tree
.
├── bin
├── cmake
├── lib
├── src
│   ├── samples
│   │   ├── test_xlog
│   │   │   └── test_xlog.cpp
│   │   └── test_xthread_pool
│   │       └── test_thread_pool.cpp
│   ├── xlog （日志系统）
│   │   ├── include
│   │   │   ├── xconfig.h
│   │   │   └── xlog.h
│   │   ├── unit_test
│   │   │   └── testmain.cpp
│   │   ├── xconfig.h.in
│   │   ├── xlog.cpp
│   │   ├── xlog_thread.cpp
│   │   └── xlog_thread.h
│   └── xthread_pool （进程池）
│       ├── include
│       │   ├── xlib.h
│       │   ├── xthread.h
│       │   └── xthread_pool.h
│       ├── unit_test （单元测试）
│       │   └── testmain.cpp
│       ├── xthread.cpp
│       └── xthread_pool.cpp
└── tools （第三方依赖）
    └── gtest-1.11.0.tar.gz
    # 这个还可以有很多，比方说：boost

15 directories, 16 files
```

## 配置：支持 find_package 之后，出现报错

```sh
~/DOCs/cpp/cmakeLearn/notes/chap8/project/src/xlog (main*) » cmake -S . -B build                                                                                   1 ↵ wangfiox@wangjins-MacBook-Pro
-- Configuring done (0.0s)
CMake Error in CMakeLists.txt:
  Target "xlog" INTERFACE_INCLUDE_DIRECTORIES property contains path:

    "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap8/project/src/xlog/include/"

  which is prefixed in the source directory.


CMake Error in CMakeLists.txt:
  Target "xlog" INTERFACE_INCLUDE_DIRECTORIES property contains path:

    "/Users/wangfiox/DOCs/cpp/cmakeLearn/notes/chap8/project/src/xlog"

  which is prefixed in the source directory.
```

这个报错的含义是：

对外接口的头文件属性（interface_include_directories property），包含源码路径。

看到啥报错就改啥。因此就是：把头文件查找路径，改为：public --> private

```cmake
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/
    ${CMAKE_CURRENT_LIST_DIR}
)
```

为什么不能让：对外接口的头文件属性包含源码路径呢？
就是：你安装的时候，肯定要让安装后的库，与源码是脱钩的。

至于包含源码路径：cmake 中用的是绝对路径

<!-- TODO 版本问题 -->
