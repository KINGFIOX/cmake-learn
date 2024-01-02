# comment - 注释

## archive runtime library输出的区别

在 CMake 中，`CMAKE_RUNTIME_OUTPUT_DIRECTORY`、`CMAKE_ARCHIVE_OUTPUT_DIRECTORY` 和 `CMAKE_LIBRARY_OUTPUT_DIRECTORY` 这三个变量用于指定不同类型的构建产物的输出目录。

1. `CMAKE_RUNTIME_OUTPUT_DIRECTORY`：这个变量用于指定可执行文件（在 Windows 下是 `.exe` 文件，在 Unix-like 系统下是没有扩展名的可执行文件）的输出目录。

2. `CMAKE_ARCHIVE_OUTPUT_DIRECTORY`：这个变量用于指定静态库（在 Windows 下是 `.lib` 文件，在 Unix-like 系统下是 `.a` 文件）的输出目录。

3. `CMAKE_LIBRARY_OUTPUT_DIRECTORY`：这个变量用于指定动态库（在 Windows 下是 `.dll` 文件，在 Unix-like 系统下是 `.so` 或 `.dylib` 文件）的输出目录。

这三个变量通常用于组织构建产物，使得构建产物可以按照类型分别存放在不同的目录中。

## 突发奇想：反汇编 与 编译过程中的汇编 的区别

`gcc -S` 和 `objdump -d` 都可以用来生成汇编代码，但它们的工作方式和输出的内容有一些不同。

1. `gcc -S`：这个命令会将源代码（如 C 或 C++）编译成汇编代码，但不会进行链接。输出的是源代码级别的汇编，包含了源代码中的函数和变量名。

2. `objdump -d`：这个命令会将已经编译和链接过的二进制文件（如 ELF 文件）反汇编成汇编代码。输出的是机器级别的汇编，通常不包含源代码中的函数和变量名，而是包含了内存地址和机器指令。

所以，`gcc -S` 更适合于理解源代码是如何被编译成汇编的，而 `objdump -d` 更适合于理解已经编译和链接过的程序的机器级别的行为。