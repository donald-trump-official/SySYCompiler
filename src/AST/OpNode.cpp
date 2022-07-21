#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string OpNode::to_string(){
	switch(_type){
		case AST_ADD: return "+";
		case AST_SUB: return "-";
		case AST_MUL: return "*";
		case AST_MOD: return "%";
		case AST_EQ: return "==";
		case AST_GT: return ">";
		case AST_LT: return "<";
		case AST_GTEQ: return ">=";
		case AST_LTEQ: return "<=";
		default: return "";
	}
}