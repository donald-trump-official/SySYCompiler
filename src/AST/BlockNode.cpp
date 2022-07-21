#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void BlockNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
	for(auto item:sons){
		item->print(level + 1);
	}
}

std::string BlockNode::to_string(){
	return *text;
}