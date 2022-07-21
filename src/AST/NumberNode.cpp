#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

std::string NumberNode::to_string(){
	std::string num_text;
	if(is_int){
		num_text += std::to_string(val.int_val);
	}else{
		num_text += std::to_string(val.float_val);
	}
	return num_text;
}