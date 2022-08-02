#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>

namespace IR{
	class Type{
	public:
		enum TypeID{
			FloatTyID,
			VoidTyID,
			LabelTyID,
			IntegerTyID,
			FunctionTyID,
			PointerTyID,
			ArrayTyID,
		};
		
		Type(TypeID ty):ID(ty){};
		TypeID get_type(){return ID;}
		bool is_float_type(){return ID == FloatTyID;}
		bool is_void_type(){return ID == VoidTyID;}
		bool is_label_type(){return ID == LabelTyID;}
		bool is_integer_type(){return ID == IntegerTyID;}
		bool is_function_type(){return ID == FunctionTyID;}
		bool is_pointer_type(){return ID == PointerTyID;}
		bool is_array_type(){return ID == ArrayTyID;}
	private:
		TypeID ID;
	};
}

#endif