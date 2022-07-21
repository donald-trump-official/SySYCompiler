#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void StmtNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
	switch(_type){
		case STMT_IF:{
			sons[0]->print(level + 1); //条件
			sons[1]->print(level + 1); //if块
			if(sons.size() >= 3){
				sons[2]->print(level + 1); //else块
			}
			break;
		}
		case STMT_WHILE:{
			sons[0]->print(level + 1); //条件
			sons[1]->print(level + 1); //循环体
			break;
		}
		case STMT_BLOCK:{
			for(auto i:sons){
				i->print(level + 1);
			}
			break;
		}
		case STMT_EXP:{
			sons[0]->print(level + 1);
			break;
		}
		case STMT_ASSIGN:{
			std::cout<<std::string((level + 1) * tab, ' ');
			std::cout<<sons[0]->to_string(); //左值
			std::cout<<"=";
			std::cout<<sons[1]->to_string(); //右值
			std::cout<<std::endl;
			break;
		}
		case STMT_RETURN:{
			if(sons.size() > 0){
				sons[0]->print(level + 1);
			}
			break;
		}
		case STMT_CONTINUE:{
			break;
		}
		case STMT_BREAK:{
			break;
		}
		default: break;
	}
}

std::string StmtNode::to_string(){
	return *text;
}

void StmtNode::set_type(StmtType t){
	_type = t;
}

StmtType StmtNode::get_type(){
	return _type;
}