#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void DimListNode::print(int level){
	std::cout<<std::string(level * tab, ' ');
	std::cout<<this->to_string()<<std::endl;
}

std::string DimListNode::to_string(){
	std::string text;
	for(auto dim:sons){
		text += dim->to_string();
	}
	return text;
}