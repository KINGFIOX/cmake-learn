# chap3 - cmake 主要语法

## if 控制流程

### 语法格式

```cmake
if (<condition>)
    <commands>
elseif (<condition>)
    <command>
else()
    <command>
endif()
```

### 基本表达式

cmake if 基本表达式，也就是`<condition>`可以有什么

1. `<constant>`常量

ON, YES, TRUE, Y 或者 非零数（包括浮点数） --> TRUE

0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串，或者以 NOTFOUND 结尾 --> FALSE

2. `<variable>`变量

非 FALSE 且 已被定义 --> TRUE

FLASE 或者 未定义 变量、环境变量 --> FALSE

宏参数不是变量（宏只是替换）

3. `<string>`字符串

字符串的值是常量 TRUE --> TRUE
