# 项目名
project(compiler)

# CMake版本
cmake_minimum_required(VERSION 3.16.3)

# C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 要求安装Flex和Bison
find_package(BISON)
find_package(FLEX)

# Flex和Bison生成指令，输出的文件都在build下
set(lexer_src ${CMAKE_BINARY_DIR}/lexer.cpp)
set(parser_src ${CMAKE_BINARY_DIR}/parser.cpp)
add_custom_command(
	OUTPUT lexer.cpp
	COMMAND flex -o ${CMAKE_BINARY_DIR}/lexer.cpp ${CMAKE_SOURCE_DIR}/src/Front/lexer.l
	DEPENDS ${CMAKE_SOURCE_DIR}/src/Front/lexer.l
)
add_custom_command(
	OUTPUT parser.cpp
	COMMAND bison -d -o ${CMAKE_BINARY_DIR}/parser.cpp ${CMAKE_SOURCE_DIR}/src/Front/parser.y
	DEPENDS ${CMAKE_SOURCE_DIR}/src/Front/parser.y
)

# 添加引用目录
include_directories(${CMAKE_SOURCE_DIR}/include/AST)
include_directories(${CMAKE_SOURCE_DIR}/include/IR)
include_directories(${CMAKE_SOURCE_DIR}/build)

# 添加源码
file(
	GLOB srcs
	src/*.cpp
	src/Front/*.cpp
	src/AST/*.cpp
	src/IR/*.cpp
	src/Optimize/*.cpp
	src/CodeGen/*.cpp
)

# 添加可执行程序
add_executable(
	compiler
	${srcs}
	${lexer_src}
	${parser_src}
)

# （make构建项目时不会执行）测试：make test
add_custom_target(
	test
	COMMAND echo ${CMAKE_BINARY_DIR}
	COMMAND cd ${CMAKE_BINARY_DIR}
	COMMAND ./compiler ../test/test.c
)