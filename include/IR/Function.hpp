#ifndef _FUNCTION_HPP_
#define _FUNCTION_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Value.hpp"
#include "BasicBlock.hpp"
#include "Argument.hpp"

namespace IR
{
	class Function:public Value{
	public:
		Function();
		void add_arg(Argument *arg);
		std::list<Argument*> &get_arg_list();
		void add_bb(BasicBlock *bb);
		std::list<BasicBlock*> &get_bb_list();
	private:
		std::list<Argument*> arg_list;
		std::list<BasicBlock*> bb_list;
	};
}

#endif