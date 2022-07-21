#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void PrimaryExpNode::print(int level){

}

std::string PrimaryExpNode::to_string(){
	std::string text;
	text += "(";
	text += sons[0]->to_string();
	text += ")";
	return text;
}