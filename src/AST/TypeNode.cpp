#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string TypeNode::to_string(){
	std::string type_text;
	switch(_type){
		case AST_VOID:{
			type_text += "void";
			break;
		}
		case AST_INT:{
			type_text += "int";
			break;
		}
		case AST_FLOAT:{
			type_text += "float";
			break;
		}
		default: break;
	}
	return type_text;
}