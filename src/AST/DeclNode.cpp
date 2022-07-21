#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void DeclNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
	sons[1]->print(level + 1);
}

std::string DeclNode::to_string(){
	std::string text = "[";
	if(is_const) text += "Decl-Const";
	else text += "Decl-Var";
	text += " ";
	text += sons[0]->to_string(); //类型
	text += "]";
	return text;
}

void DeclNode::set_const_decl(bool cst){
	is_const = cst;
}

bool DeclNode::is_const_decl(){
	return is_const;
}