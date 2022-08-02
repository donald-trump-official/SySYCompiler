#ifndef _VALUE_HPP_
#define _VALUE_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Type.hpp"

namespace IR
{
	class Value{
	public:
		Value();
		std::string get_name();
		void set_name(std::string &_name);
		Type *get_type();
		std::vector<Value*> &get_use_list();
		void add_use(Value *v);
		virtual void print();
	private:
		Type *ty;
		std::list<Value*> use_list;
		std::string name;
	};
}

#endif