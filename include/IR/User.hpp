#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Value.hpp"

namespace IR
{
	class User:public Value{
	public:
		User();
		Value* get_operand(int num);
		std::vector<Value*> get_operand_list();
		bool set_operand(int num, Value* op);
		void add_operand(Value *op);
	private:
		std::vector<Value*> operand_list;
	};
}

#endif