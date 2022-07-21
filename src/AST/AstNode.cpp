#include "ast.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

AstNode *ast_root = nullptr;


AstNode::AstNode(){
	text = nullptr;
}

AstNode::AstNode(const char *str){
	if(str == nullptr){
		text = nullptr;
	}else{
		text = new std::string(str);
	}
}

void AstNode::add_son(const char *str){
	AstNode *temp = nullptr;
	if(str == nullptr) temp = new AstNode();
	else temp = new AstNode(str);
	sons.push_back(temp);
}

void AstNode::add_son(AstNode *son_node){
	if(son_node != nullptr) sons.push_back(son_node);
	else return;
}

std::string& AstNode::get_text(){
	return *text;
}

std::vector<AstNode*> AstNode::get_sons(){
	return sons;
}

void AstNode::pre_trversal(AstNode *root, int level){
	if(root == nullptr){
		std::cout<<"error: root is NULL"<<std::endl;
		return;
	}
	for(int i=0; i<level; i++) std::cout<<"  ";
	std::cout<<root->to_string()<<std::endl;
	for(auto i:root->sons){
		pre_trversal(i, level + 1);
	}
	return;
}

void AstNode::print(int level){
	std::cout<<std::string(level * tab, ' ')<<this->to_string()<<std::endl;
	for(auto i:sons){
		i->print(level + 1);
	}
}

std::string AstNode::to_string(){
	return *text;
}

