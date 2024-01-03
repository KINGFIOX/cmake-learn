# comment

## 缓存变量 - internal

在 CMake 中，`INTERNAL` 是一个用于 `set` 命令的 `CACHE` 选项的类型，用于创建一个内部缓存变量。

内部缓存变量主要用于存储 CMake 或项目的内部状态，而不是用于用户设置。
这些变量不会显示在 CMake GUI 的界面上，用户也不能通过命令行选项来修改它们。

例如，以下的代码会创建一个名为 `MY_INTERNAL_VAR` 的内部缓存变量，
并设置其值为 `my_value`：

```cmake
set(MY_INTERNAL_VAR "my_value" CACHE INTERNAL "An internal variable")
```

在这个例子中，`MY_INTERNAL_VAR` 变量的值可以在 CMakeLists.txt 文件中使用，但用户不能通过 CMake GUI 或命令行选项来查看或修改它。

## 缓存变量 - string

在 CMake 中，`STRING` 是 `set` 命令的 `CACHE` 选项的一种类型，用于创建一个字符串类型的缓存变量。

当你设置一个缓存变量的类型为 `STRING` 时，这个变量的值将被视为一个字符串。这意味着你可以在这个变量中存储任何文本内容。

例如，以下的代码会创建一个名为 `MY_STRING_VAR` 的字符串类型的缓存变量，并设置其值为 `my_string_value`：

```cmake
set(MY_STRING_VAR "my_string_value" CACHE STRING "A string variable")
```

在这个例子中，`MY_STRING_VAR` 变量的值可以在 CMakeLists.txt 文件中使用，用户也可以通过 CMake GUI 或命令行选项 `-D` 来查看或修改它。例如，用户可以使用以下的命令来修改 `MY_STRING_VAR` 变量的值：

```bash
cmake -DMY_STRING_VAR=new_value ..
```
