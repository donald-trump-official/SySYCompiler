#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void LValNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
}

std::string LValNode::to_string(){
	std::string text;
	text += sons[0]->to_string(); //标识符
	text += sons[1]->to_string(); //数组引用偏移
	return text;
}