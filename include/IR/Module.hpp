#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "Value.hpp"
#include "Function.hpp"
#include "GlobalVar.hpp"

namespace IR
{
	class Module{
	public:
		Module();
		void add_function(Function *func);
		void add_global_def(GlobalVar *glob);
	private:
		std::map<std::string, Value*> symbol_table;
		std::list<Function*> function_list;
		std::list<GlobalVar*> global_list;
	};
}

#endif