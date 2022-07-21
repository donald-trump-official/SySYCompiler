#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

void FuncDefNode::print(int level){
	std::cout<<std::string(level * tab, ' ');
	std::cout<<sons[0]->to_string()<<" ";
	std::cout<<sons[1]->to_string()<<" ";
	for(auto param:sons[2]->get_sons()){ //每个参数
		std::cout<<"[";
		// for(auto j:i->get_sons()){
		// 	std::cout<<j->to_string()<<" ";
		// }
		auto i = param->get_sons();
		std::cout<<i[0]->to_string()<<" "; //类型
		std::cout<<i[1]->to_string(); //标识符
		if(i.size() >= 3){
			//参数是数组
			std::cout<<"[]"<<i[2]->to_string(); //维数
		}
		std::cout<<"]";
	}
	std::cout<<std::endl;
	sons[3]->print(level + 1);
}