#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string InitValNode::to_string(){
	std::string text;
	text += sons[0]->to_string();
	return text;
}