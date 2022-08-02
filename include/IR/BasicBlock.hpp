#ifndef _BASI_CBLOCK_HPP_
#define _BASIC_BLOCK_HPP_

#include <string>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Value.hpp"
#include "Instruction.hpp"

namespace IR
{
	class BasicBlock:public Value{
	public:
		enum InstrID{
			// Terminator Instructions
			ret,
			br,
			// Standard binary operators
			add,
			sub,
			mul,
			sdiv,
			srem,
			// Float binaru opeartors
			fadd,
			fsub,
			fmul,
			fdiv,
			// Memory operators
			alloca,
			load,
			store,
			// Other operators
			cmp,
			fcmp,
			phi,
			call,
			getelementptr, 
			// Zero extend
			zext,
			// type cast bewteen float and singed integer
			fptosi,
			sitofp,
    	};
		BasicBlock();
		void add_instr(Instruction *instr);
	private:
		std::list<Instruction*> instr_list;
		InstrID id;
	};
}

#endif