#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void DefNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
}

std::string DefNode::to_string(){
	std::string text;
	text += sons[0]->to_string(); //标识符
	text += sons[1]->to_string(); //数组维数
	if(sons.size() >= 3){
		//有初始值
		text += "=";
		text += sons[2]->to_string();
	}
	return text;
}