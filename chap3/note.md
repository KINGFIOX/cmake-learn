# chap3 - cmake 生成表达式和文件操作

## 简介

### 什么是生成器表达式

- 替代复杂的 if

- 在构建系统生成期间 估计生成器表达式以 生成 特定于 每个构建配置的信息

配置、生成、构建

之前的命令：`cmake -S . -B build`是将：配置与生成一起做的

生成指的是：生成 makefile、或者是生成 "vs 项目"

配置：是将所有的 cmake 代码都走一遍，但是碰到`add_executable`只是先将标注存下来

所以：我们之前会有 在`add_executable`下，依然有`target_link`之类的语法。
这是因为：所有配置完了以后，最后才执行这个`add_executable`

- 大多数 cmake 命令在配置的时候执行

- 如果你想要他们在 构建 或者 安装 的时候运行呢？

可以概括为两个方面：

1. 简化语法
2. 在特定的场景下会用

### 使用场景

修改目标配置：

1. target_link_libraries

（之前有讲过：修改目标属性）

### 布尔 生成器表达式

1. 逻辑表达式

- `$<BOOL:string>`判断 string 是不是 TRUE，前面有讲过：ON TRUE 等是真
- `$<AND:conditions>`
- `$<OR:conditions>`
- `$<NOT:condition>`

（这些会与下面的 “字符串值生成器表达式” > “条件表达式” 配合使用）

2. 字符串比较

- `$<STREQUAL:string1, string2>` 字符串的比较
- `$<EQUAL:value1, value2>` 数字的比较

3. 变量查询

- `$<TARGET_EXISTS:target>`
- `$<CONFIG:cfgs>`
- `$<>`

### 字符串值 生成器表达式

1. 条件表达式

- `$<condition:true_string>`
- `$<IF:condition, true_string, false_string>`

2. 字符串转换

- `$<LOWER_CASE:str>`大小写
-

3. 变量查询

- `$<CONFIG>`
- `$<PLATFORM_ID>`

4. 目标相关的查询

- `$<TARGET_NAME_IF_EXISTS:tgt>`
- `$<TARGET_FILE:tgt>` 目标文件的 绝对路径
- `$<TARGET_PDB_FILE:tgt>`
- `$<TARGET_PROPERTY:tgt.prop>`

### 调试

注意一下：生成器表达式都是在：生成的时候有效的。
因此：message 并不能打印 生成器表达式 相关的信息，
因为 message 只是在 配置

```cmake
add_custom_target(genexdebug COMMAND ${CMAKE_COMMAND} -E echo "$<...>")  # 在生成的时候会echo
```

## 代码示例 1:

cmake 配置：

```cmake
add_executable(${PROJECT_NAME} expr.cc)
# 为目标的编译增加一些 宏变量
target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC # 后面再说，这个和依赖有关系
    "$<$<BOOL:ON>:TEST1=123>"
)
```

（逻辑运算 要与 条件表达式 一起使用）

cpp 代码：

```cpp
int main(void)
{
    cout << "hello" << endl;
#ifdef TEST1
    cout << TEST1 << endl;
#endif
}
```

### 测试生成表达式的方式

上面是，通过运行 C++可执行文件的方式，很麻烦，因为大型项目就要编译一会儿。

下面有两种方式：

1. 利用 cmake 的错误来查看（这种方式，还是有些操蛋了）

```cmake
# 利用cmake的错误来查看  --> cmake error in cmakelists.txt
# target_include_directories( ${PROJECT_NAME} PUBLIC "$<AND:1,0>")
target_include_directories(${PROJECT_NAME} PUBLIC "$<OR:1,0>")
```

输出：

```sh
[cmake] CMake Error in CMakeLists.txt:
[cmake]   Found relative path while evaluating include directories of "expr":
[cmake]
[cmake]     "1"
```

原本应该：`target_include_directories`应该包含的是：路径。
但是我们传入的却是：生成器表达式

然后我们可以通过这个误传入的，判断我们写的这个：生成表达式 有没有问题

2. 生成一个自定义目标，让他去显示内容（官方给的方法）

```cmake
message(
    $<
        $<
            NOT:$<
                BOOL:${LIB}
            >
        >:STATIC
    >
)
```

输出：（message 打印的效果）

```sh
[cmake] $<$<NOT:$<BOOL:$<LIB>>>:STATIC>
```

所以我们这里用的方法是：`add_custom_target`

```cmake
add_custom_target(
    gen
    COMMAND ${CMAKE_COMMAND} -E echo "$<$<NOT:$<BOOL:${LIB}>>:STATIC=1>"
)
```

输出：

使用自定义命令

```sh
~/DOCs/cmakeLearn/notes/chap3/301expr (main*) » cmake --build build --target gen
```

```sh
~/DOCs/cmakeLearn/notes/chap3/301expr (main*) » cmake --build build --target gen
STATIC=1
Built target gen
```

### 变量查询

1. config

```cmake
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "$<CONFIG>"
)
```

输出：

（如果是 windows，默认会有 Debug，也会有 release）

```sh
[cmake] CMake Error in CMakeLists.txt:
[cmake]   Found relative path while evaluating include directories of "expr":
[cmake]
[cmake]     "Debug"
```

2. 系统平台

```cmake
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "$<PLATFORM_ID>"
)
```

输出：

```sh
[cmake] CMake Error in CMakeLists.txt:
[cmake]   Found relative path while evaluating include directories of "expr":
[cmake]
[cmake]     "Darwin"
```

#### 其中之一

就是查询结果就是：如果有其中之一，那么返回 "1"; 否则返回 "0"

```cmake
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "$<PLATFORM_ID: Windows, Linux>"
)
```

在我的电脑上，返回 0

### 条件表达式

```cmake
set(LIB ON)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "$<IF:$<BOOL:${LIB}>, fuck, you>"
)
```

### 目标查询

```cmake
set(var $<TARGET_FILE:expr>)
add_custom_target(
    gen
    COMMAND ${CMAKE_COMMAND} -E echo "${var}"
)

```

输出：

```sh
~/DOCs/cmakeLearn/notes/chap3/301expr (main*) » cmake --build build --target gen
[ 50%] Building CXX object CMakeFiles/expr.dir/expr.cc.o
[100%] Linking CXX executable expr
[100%] Built target expr
/Users/wangfiox/DOCs/cmakeLearn/notes/chap3/301expr/build/expr
[100%] Built target gen
```

## 提示

有时候注意一下错误，比方说重名错误就会有提示：see documentation for policy CMP0002 for more details
