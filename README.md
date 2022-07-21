# YCCC编译器

## 介绍

SysY语言编译器，SysY语言标准见比赛组委官方文件，2022年比赛的标准加入了浮点数。

编译器整体用C++实现，前端用Flex和Bison编写，仓库中上传了Flex和Bison的脚本，但没有它们生成的C++代码和最终的可执行文件，构建方法将在后文中介绍。目前还在制作前端，编译器还不能解析SysY所有的语法，能够解析部分语法并生成简单的语法树，解析完成后会对生成的AST做一次先序遍历。

### 关于AST

Blcok下每个Stmt是并列的，每个CompUnit都是根节点的子节点。

AST节点类型（AstNode派生类）：

| 类名 | 描述     | 例子           | 属性 |
| ---- | -------- | -------------- | ---- |
|      | 变量声明 | `int a;`       |      |
|      | 变量定义 | `a=1;`         |      |
|      | 函数定义 | `int main(){}` |      |
|      |          |                |      |
|      |          |                |      |
|      |          |                |      |



### 语义检查

1. 变量使用前先声明
2. 函数返回值与函数定义是否一致
3. const变量不能赋值
4. 赋值语句两边类型是否一致，是否可以类型转换

符号表设计



### 关于IR

目前暂定直接使用LLVM IR，`-O0`优化（禁用优化）时，clang生成的LLVM IR已经具有SSA结构，所以我们生成的SSA也应该具有SSA结构，方便后续寄存器分配以及进一步优化。

这里列出实现SysY语言需要用到的所有LLVM IR指令，注意，这里的指令是我们期望自己的编译器生成的语句，与clang生成的会有一些不同：

**函数定义**

```
define dso_local i32 @main() {}
```

**局部变量声明（alloca）**

`%1`中存放着一个内存地址，访问这个地址的值时要用`i32*`

```
%1 = alloca i32
```

**局部变量赋值（store）**

将0存入`%1`中地址指向的内存

```
store i32 0, i32* %1
```

**局部变量取值（load）**

将`%2`中地址处的值取出，存入`%4`

```
%4 = load i32, i32* %2
```

**比较（icmp）**

比较`%4`和`%5`中的值，将结果存入`%6`，相等1，不等0，`%6`是`i1`类型，即1位布尔型

```
%6 = icmp eq i32 %4, %5
```

`eq`是相等，`sgt`是大于，`slt`是小于

**有条件跳转**

判断`%6`，如果为1跳转到`%7`标记的基本块，为0跳转到`%8`标记的基本块

```
br i1 %6, label %7, label %8
```

**函数返回**

返回`%10`中的值

```
ret i32 %10
```

**算数运算**

第一个和第二个操作数都可以是寄存器或立即数

```
%3 = add i32 %2, 1
%5 = sub i32 %4, 1
%7 = mul i32 %6, 2
%9 = sdiv i32 %8, 2
```

## 构建方法

Linux下构建：

```bash
make
```

删除所有生成的C++代码和可执行程序：

```bash
make clean
```

## 测试

用于测试的源代码文件放在`./test/`目录下，可执行文件的名称是`parser`，假如现在解析名为`func_decl.txt`的源代码文件，命令是：

```bash
./parser ./test/func_decl.c
```

## 代码结构

```
│  .gitignore
│  ast.cpp				AST相关
│  ast.hpp				AST头文件
│  lexer.cpp
│  lexer.l				Flex脚本
│  main.cpp				主函数在这里定义
│  Makefile				MakeFile
│  parser				可执行程序
│  parser.cpp
│  parser.hpp
│  parser.y				Bison脚本
└─test					测试用例目录
        func_decl.txt
```

## 问题

### 还未实现的

声明多个变量

```
int a,b,c;
```

函数参数

```
int f(int a, int b){}
```

函数调用

```
fun(0);
```

if和while

```
if(cond){}else{}
while(cond){}
```
