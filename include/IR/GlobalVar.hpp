#ifndef _OPERATOR_HPP_
#define _OPERATOR_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Value.hpp"
#include "User.hpp"
#include "Cosnt.hpp"

namespace IR
{
	class GlobalVar:public User{
	public:
		GlobalVar();
		bool is_const();
	private:
		const bool is_const_var;
		Const* init_value;
	};
}

#endif