#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string InitValListNode::to_string(){
	std::string text = "{";
	for(auto init:sons){
		text += init->to_string();
		text += ",";
	}
	text.pop_back();
	text += "}";
	return text;
}