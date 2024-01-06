# cmake install 部署项目

- 测试代码准备
- 安装目标
- 安装文件
- 安装目录
- 安装时执行程序
- 安装指定的模块
- 自定义 find_package 可导入库

## 安装时执行程序

```cmake
# ###### 安装目标 ########

# 安装目标 desination 指定 相对 cmake_install_prefix 的输出路径
# cmake_install_prefix默认是/usr/local
# windows的默认cmake_install_prefix是 C:/Program Files (x86)/
# 可以在生成的时候 cmake -S . -B build -DCMAKE_INSTALL_PREFIX=<path>
install(TARGETS slib dlib ${PROJECT_NAME} DESTINATION bin)

# cmake --install build（这个和build平行的）
```

当然这个`cmake -D`也可以是

```cmake
set(CMAKE_INSTALL_PREFIX ./out)
```

windows 中，还可以指定安装版本`cmake --install build Debug`

### 分配不同的路径

上面我们是将所有的.a、.lib、.out 之类的，都安装到了一个路径。

但是，我们的`/usr/local`里面，也有`/usr/local/bin`也有`/usr/local/lib`，这个肯定是要再细分的

## 安装目标（有 5 种目标）

- runtime

由 add_executable 创建，
包含：windows 动态连接库 dll 文件、可执行文件。放到 bin

```cmake

```

- archive （归档）

windows 动态库到处符号 .lib .dll

静态库

- library

动态库

- public_header、private_header

```cmake
# ###### 安装目标 ########
set(CMAKE_INSTALL_PREFIX ./out)

# cmake --install build（这个和build平行的）
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin # 执行程序
)

# 设置头文件属性
set_target_properties(slib PROPERTIES PUBLIC_HEADER include/slib.h)
set_target_properties(slib PROPERTIES PRIVATE_HEADER include/slib_pri.h)

install(TARGETS slib dlib
    RUNTIME DESTINATION bin # 执行程序和dll文件输出
    ARCHIVE DESTINATION lib # 静态库和windows动态库导出符号.lib
    LIBRARY DESTINATION lib # linux和mac的动态库.so 和 .lib导出到lib种
    PRIVATE_HEADER DESTINATION include
    PUBLIC_HEADER DESTINATION inc
)
```

## debug release 不同输出路径

```cmake
install(TARGETS slib dlib
    CONFIGURATIONS Debug # <-- 改了这里
    RUNTIME DESTINATION debug/bin # 执行程序和dll文件输出
    ARCHIVE DESTINATION debug/lib # 静态库和windows动态库导出符号.lib
    LIBRARY DESTINATION debug/lib # linux和mac的动态库.so 和 .lib导出到lib种
    PRIVATE_HEADER DESTINATION debug/include
    PUBLIC_HEADER DESTINATION debug/inc
)
```

要先 生成 debug 版 `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug `的 makefile

再安装 debug 版

```cmake
cmake --build build
cmake --install build --config Debug
```

编译并生成 Debug 版本

## cmake install 安装文件

上面的 install 是 TARGETS 的，下面是 FILES

### 文件安装到指定目录

```cmake
# 文件安装到指定目录
install(FILES a.h b.h
    DESTINATION include
)
```

### 目标可选 optional 目标不存在不出错

```cmake
install(FILES c.h
    DESTINATION inc OPTIONAL
)
```

### 文件类型 TYPE

文件类型就这么多

![install](./image/install.png)

```cmake
include(GNUInstallDirs)
message("CMAKE_INSTALL_DATAROOTDIR = ${CMAKE_INSTALL_DATAROOTDIR}") # 默认是share
install(FILES a.h TYPE DOC) # <DATAROOT dir>/doc
install(FILES b.h TYPE LIB) # /lib
```

要`include(GNUInstallDirs)`才能看到`CMAKE_INSTALL_DATAROOTDIR`

否则`message`输出：

```sh
[cmake] CMAKE_INSTALL_DATAROOTDIR =
```

### 文件权限

既然有了文件，对应的肯定有文件的权限

默认权限是：owner_read owner_write group_read world_read，也就是 644

```cmake
install(FILES a.h
    DESTINATION pub
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ
)
```

可以看到：

```sh
~/DOCs/cpp/cmakeLearn/notes/chap5/502cmake_install_file/out/pub (main*) » ls -l
total 0
-rw-r-----  1 wangfiox  staff     0B Jan  6 14:49 a.h
```

## 自定义 find_package 可导入库
