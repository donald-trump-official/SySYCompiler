#include <cassert>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <list>
#include "parser.hpp"
#include "ast.hpp"
#include "ir.hpp"

using namespace std;

extern int yyparse();
extern FILE* yyin;
extern std::ofstream f_ir;

int main(int argc, const char *argv[]) {
	// 参数解析
	if(argc != 2){
		cout<<"error: require an input file"<<endl;
		return 1;
	}
	// 打开输入输出文件
	f_ir.open("./ir_out.ll", ios::out);
	yyin = fopen(argv[1], "r");
	assert(yyin);
	// 初始化根节点
	ast_root = new AstNode("[Root]");
	// 文法语法解析
	yyparse();
	cout<<"parser done"<<endl;
	// 打印AST
	// AstNode::pre_trversal(ast_root, 0);
	ast_root->print(0);
	// AstNode::pre_trversal(ast_root, 0);
	// 关闭文件等
	f_ir.close();
	return 0;
}
