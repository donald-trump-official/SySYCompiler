#ifndef _CONST_HPP_
#define _COSNT_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Value.hpp"
#include "User.hpp"

namespace IR
{
	class Const:public User{
	public:
		Const();
	};

	class ConstInt:public Const{
	public:
		ConstInt();
		int get_value();
		void set_value(int val);
	private:
		int value;
	};

	class ConstFloat:public Const{
	public:
		ConstFloat();
		double get_value();
		void set_value(double val);
	private:
		double value;
	};

	class ConstArray:public Const{
	public:
		ConstArray();
		Const *at(int i);
		void add_value(Const *val);
	private:
		int length;
		Const *ary;
	};
}

#endif