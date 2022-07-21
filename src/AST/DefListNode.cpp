#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void DefListNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
	for(auto def:sons){
		def->print(level + 1);
	}
}

std::string DefListNode::to_string(){
	return std::string("[DefList]");
}