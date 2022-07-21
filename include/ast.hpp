#include <list>
#include <string>
#include <vector>
#include "parser.hpp"
#include "ir.hpp"

#ifndef AST
#define AST

extern std::ofstream f_ir;

enum AstOpType {AST_ADD, AST_SUB, AST_MUL, AST_DIV, AST_MOD, AST_AND, AST_OR, AST_NOT, AST_GT, AST_LT, AST_EQ, AST_NEQ, AST_GTEQ, AST_LTEQ};
enum AstDataType {AST_VOID, AST_INT, AST_FLOAT};
enum StmtType {STMT_IF, STMT_WHILE, STMT_EXP, STMT_ASSIGN, STMT_BLOCK, STMT_NONE, STMT_RETURN, STMT_BREAK, STMT_CONTINUE};

class AstNode{
protected:
	std::vector<AstNode*> sons;
	std::string* text;
	const int tab = 2;
public:
	AstNode();
	AstNode(const char *str);
	void add_son(const char *str);
	void add_son(AstNode *son_node);
	std::string& get_text();
	std::vector<AstNode*> get_sons();
	static void pre_trversal(AstNode *root, int level);
	virtual std::string to_string();
	virtual void print(int level);
};

class FuncDefNode:public AstNode{
public:
	FuncDefNode(const char *str):AstNode(str){};
	void print(int level) override;
	// std::string to_string() override final;
};

class DeclNode:public AstNode{
private:
	bool is_const;
public:
	DeclNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
	void set_const_decl(bool cst);
	bool is_const_decl();
};

class DefListNode:public AstNode{
public:
	DefListNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class DefNode:public AstNode{
public:
	DefNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class InitValListNode:public AstNode{
public:
	InitValListNode(const char *str):AstNode(str){};
	std::string to_string() override;
};

class InitValNode:public AstNode{
public:
	InitValNode(const char *str):AstNode(str){};
	std::string to_string() override;
};

class DimListNode:public AstNode{
public:
	DimListNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class DimNode:public AstNode{
public:
	DimNode(const char *str):AstNode(str){};
	std::string to_string() override;
};

class BlockNode:public AstNode{
public:
	BlockNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class StmtNode:public AstNode{
private:
	StmtType _type;
public:
	StmtNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
	void set_type(StmtType t);
	StmtType get_type();
};

class ExpNode:public AstNode{
public:
	ExpNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class PrimaryExpNode:public AstNode{
public:
	PrimaryExpNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class LValNode:public AstNode{
public:
	LValNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class CallFuncNode:public AstNode{
public:
	CallFuncNode(const char *str):AstNode(str){};
	void print(int level) override;
	std::string to_string() override;
};

class OpNode:public AstNode{
private:
	AstOpType _type;
public:
	OpNode(const char *str):AstNode(str){};
	OpNode(AstOpType t):_type(t){};
	void set_op(AstOpType t);
	std::string to_string() override;
};

class NumberNode:public AstNode{
private:
	union {
		int int_val;
		double float_val;
	} val;
	bool is_int;
public:
	NumberNode(const char *str):AstNode(str){};
	void set_int(int vi){val.int_val = vi; is_int = true;}
	void set_float(double vf){val.float_val = vf; is_int = false;}
	int get_int(){return val.int_val;}
	double get_float(){return val.float_val;}
	std::string to_string() override;
};

class TypeNode:public AstNode{
private:
	AstDataType _type;
public:
	TypeNode(const char *str):AstNode(str){};
	TypeNode(AstDataType t):_type(t){};
	void set_type(AstDataType t){_type = t;}
	AstDataType get_type(){return _type;}
	std::string to_string() override;
};

extern AstNode* ast_root;

#endif