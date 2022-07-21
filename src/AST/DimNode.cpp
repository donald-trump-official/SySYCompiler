#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string DimNode::to_string(){
	std::string text;
	text += "[";
	text += sons[0]->to_string(); //维数表达式
	text += "]";
	return text;
}