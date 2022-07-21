#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void ExpNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
}

std::string ExpNode::to_string(){
	std::string text;
	for(auto e:sons){
		text += e->to_string();
	}
	return text;
}