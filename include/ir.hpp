#include <string>
#include <fstream>

#ifndef IR
#define IR

//LLVM IR指令类型
enum IRInsType{
	IR_DEFINE, IR_ALLOCA, IR_STORE, IR_LOAD, IR_ICMP, IR_BR, IR_RET, IR_ADD, IR_SUB, IR_MUL, IR_DIV
};

//IR数据类型，目前包括1位布尔值I1、32位有符号整数I32和占位符VOID
enum IRDataType{
	IR_VOID, IR_I1, IR_I32
};

//icmp指令比较的类型，EQ相等，SGT大于，SLT小于
enum IcmpType{
	IR_EQ, IR_SGT, IR_SLT
};

//有些指令的操作数可以是立即数或寄存器，
typedef struct Operand{
	bool is_reg;
	union{
		int reg;
		int imm;
	} op;
} Operand;


class IRInstruction{
protected:
	//指令类型
	IRInsType type;
public:
	//构造函数，初始化指令类型
	IRInstruction(IRInsType t);
	//生成文本LLVM IR，写入文件是全局流文件（TODO）
	virtual int gen_text();
	//获取指令类型
	IRInsType get_type();
};

// 全局变量定义
class IRGlobal{
private:
	std::string *ident;
	IRDataType val_type;
	bool is_const;
public:
	IRGlobal(const char *id, IRDataType type, bool is_const);
	int gen_text();
};

// 函数定义
class IRDefine: public IRInstruction{
private:
	//函数名（不带@）
	std::string *ident;
	//函数返回类型
	IRDataType rt_type;
public:
	//构造函数，初始化所有成员属性
	IRDefine(IRDataType rt, const char *fname);
	std::string& get_name();
	IRDataType get_rt_type();
	int gen_text();
};

class IRAlloca: public IRInstruction{
private:
	//分配后储存地址的临时寄存器编号
	int rt_reg;
	//分配的空间类型
	IRDataType alloc_type;
public:
	//构造函数，初始化所有成员属性
	IRAlloca(int reg, IRDataType at);
	int gen_text();
};

class IRStore: public IRInstruction{
private:
	//存入内存的数据类型
	IRDataType data_type;
	//存放地址的寄存器编号
	int addr_reg;
	//待存入的数据
	int num;
public:
	IRStore(IRDataType dt, int reg, int num);
	int gen_text();
};

class IRLoad: public IRInstruction{
private:
	//从内存中取出的数放入的寄存器编号
	int tar_reg;
	//存放地址的寄存器
	int addr_reg;
public:
	IRLoad(int tar, int addr);
	int gen_text();
};

class IRIcmp: public IRInstruction{
private:
	//比较结果存放的寄存器编号
	int tar_reg;
	//比较类型，EQ相等，SGT大于，SLT小于
	IcmpType cmp_type;
	//第一个比较数
	Operand num1;
	//第二个比较数
	Operand num2;
public:
	IRIcmp(int tar, IcmpType c_type, bool n1_is_reg, int n1, bool n2_is_reg, int n2);
	int gen_text();
};

class IRBr: public IRInstruction{
private:
	//检查的寄存器
	int flg_reg;
	//条件为真跳转的标签
	int t_label;
	//条件为假跳转的标签
	int f_label;
public:
	IRBr(int flg, int l_true, int l_false);
	int gen_text();
};

class IRRet: public IRInstruction{
private:
	//返回的数据类型，包括I32，I1和VOID
	IRDataType ret_type;
	//返回值，如果返回类型是VOID
	Operand ret_reg;
public:
	IRRet(IRDataType type, bool rt_is_reg, int rt_val);
	int gen_text();
};

class IRArith: public IRInstruction{
private:
	//结果寄存器
	int res_reg;
	//操作数1
	Operand op1;
	//操作数2
	Operand op2;
public:
	IRArith(int res, bool n1_is_reg, int n1, bool n2_is_reg, int n2);
	int gen_text();
};



#endif
