#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void CallFuncNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
}

std::string CallFuncNode::to_string(){
	std::string text;
	text += sons[0]->to_string();
	text += "(";
	for(auto rp:sons[1]->get_sons()){
		text += rp->to_string();
		text += ",";
	}
	text.pop_back();
	text += ")";
	return text;
}