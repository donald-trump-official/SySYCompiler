%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stack>
#include "ast.hpp"

using namespace std;

int yylex();
void yyerror(const char *s);

stack<BlockNode*> block_stack;        // 用于解决递归规则的数据结构，栈顶是当前block的节点，block内的Stmt都会直接挂在block下，而不会以递归的形式存在
BlockNode *cur_block = nullptr;
AstNode *cur_funcfparams = nullptr;
stack<AstNode*> funcrparams_stack;
AstNode *cur_funcrparams = nullptr;
DefListNode *cur_deflist = nullptr;
DimListNode *cur_dimlist = nullptr;
stack<DimListNode*> dimlist_stack;
InitValListNode *cur_initvallist = nullptr;
stack<InitValListNode*> initvallist_stack;

%}

%union {
  std::string *str_val;
  int int_val;
  double float_val;
  AstNode *node;
  OpNode *op_node;
  NumberNode *number_node;
  TypeNode *type_node;
  FuncDefNode *funcdef_node;
  DeclNode *decl_node;
  DefListNode *deflist_node;
  DefNode *def_node;
  InitValNode *initval_node;
  DimListNode *dimlist_node;
  DimNode *dim_node;
  BlockNode *block_node;
  StmtNode *stmt_node;
  ExpNode *exp_node;
  PrimaryExpNode *primaryexp_node;
  CallFuncNode *callfunc_node;
  LValNode *lval_node;
}

/* 终结符 */
%token INT FLOAT CONST
%token VOID RETURN
%token IF ELSE
%token WHILE BREAK CONTINUE
%token ADD SUB MUL DIV MOD
%token ASSIGN
%token EQUAL NEQUAL GT LT GTEQ LTEQ
%token AND OR NOT
%token LCURLY RCURLY
%token LSQBRAC RSQBRAC
%token LBRACE RBRACE
%token SEMI COMMA
%token <str_val> IDENT
%token <int_val> INT_CONST
%token <float_val> FLOAT_CONST

/* 非终结符 */
%type <funcdef_node> FuncDef
%type <decl_node> Decl ConstDecl VarDecl
%type <node> FuncFParams FuncRParams FuncFParam
%type <block_node> Block
%type <node> BlockItem
%type <stmt_node> Stmt
%type <dim_node> Dim
%type <dimlist_node> DimList
%type <deflist_node> ConstDefList VarDefList
%type <def_node> VarDef ConstDef
%type <initval_node> InitVal InitValList
%type <type_node> BType
%type <exp_node> Exp AddExp MulExp UnaryExp PrimaryExp
%type <op_node> UnaryOp
%type <exp_node> Cond LOrExp LAndExp EqExp RelExp
%type <lval_node> LVal
%type <number_node> Number

%%
/* ========== 编译单元 ========== */
CompUnit
  : Decl {
    ast_root->add_son($1);
  }
  | CompUnit Decl {
    ast_root->add_son($2);
  }
  | FuncDef {
    ast_root->add_son($1);
  }
  | CompUnit FuncDef {
    ast_root->add_son($2);
  }
  ;

FuncDef
  : BType IDENT LBRACE FuncFParams RBRACE Block {
    $$ = new FuncDefNode("[FuncDef]");
    $$->add_son($1);
    $$->add_son($2->c_str());
    $$->add_son(cur_funcfparams);
    $$->add_son($6);
  }
  | VOID IDENT LBRACE FuncFParams RBRACE Block {
    $$ = new FuncDefNode("[FuncDef]");
    $$->add_son(new TypeNode(AST_VOID));
    $$->add_son($2->c_str());
    $$->add_son(cur_funcfparams);
    $$->add_son($6);
  }
  ;

FuncFParams
  : {
    cur_funcfparams = new AstNode("[FuncFParams]");
  }
  | FuncFParam {
    cur_funcfparams = new AstNode("[FuncFParams]");
    cur_funcfparams->add_son($1);
  }
  | FuncFParams COMMA FuncFParam {
    cur_funcfparams->add_son($3);
  }
  ;

FuncFParam
  : BType IDENT {
    $$ = new AstNode("[FuncFParam]");
    $$->add_son($1);
    $$->add_son($2->c_str());
    // $$->add_son(new DimListNode("DimList"));
  }
  | BType IDENT LSQBRAC RSQBRAC DimList {
    $$ = new AstNode("[FParam-Ary]");
    $$->add_son($1);
    $$->add_son($2->c_str());
    $$->add_son(cur_dimlist);
    dimlist_stack.pop();
    if(!dimlist_stack.empty()) cur_dimlist = dimlist_stack.top();
    else cur_dimlist = nullptr;
  }
  ;

Block
  : LCURLY BlockItem RCURLY {
    $$ = cur_block;
    block_stack.pop();
    if(!block_stack.empty()){
      cur_block = block_stack.top();
    }
  }
  ;

BlockItem
  : {
    cur_block = new BlockNode("[Block]");
    block_stack.push(cur_block);
  }
  | BlockItem Stmt {
    $$ = new AstNode("[BlcokItem-Stmt]");
    $$->add_son($2);
    cur_block->add_son($$);
  }
  | BlockItem Decl {
    $$ = new AstNode("[BlcokItem-Decl]");
    $$->add_son($2);
    cur_block->add_son($$);
  }
  ;

Stmt
  : RETURN SEMI { /*返回*/
    $$ = new StmtNode("[Stmt-Return]");
    $$->set_type(STMT_RETURN);
  }
  | RETURN Exp SEMI { /*返回值*/
    $$ = new StmtNode("[Stmt-Return]");
    $$->add_son($2);
    $$->set_type(STMT_RETURN);
  }
  | BREAK SEMI { /*break语句*/
    $$ = new StmtNode("[Stmt-Break]");
    $$->set_type(STMT_BREAK);
  }
  | CONTINUE SEMI { /*continue语句*/
    $$ = new StmtNode("[Stmt-Continue]");
    $$->set_type(STMT_CONTINUE);
  }
  | IF LBRACE Cond RBRACE Stmt ELSE Stmt { //TODO：此处有1处移进/规约冲突
    $$ = new StmtNode("[Stmt-If]");
    $$->add_son($3);
    $$->add_son($5);
    $$->add_son($7);
    $$->set_type(STMT_IF);
  }
  | IF LBRACE Cond RBRACE Stmt { /*没有else的if语句*/
    $$ = new StmtNode("[Stmt-If]");
    $$->add_son($3);
    $$->add_son($5);
    $$->set_type(STMT_IF);
  }
  | WHILE LBRACE Cond RBRACE Stmt { /*while循环*/
    $$ = new StmtNode("[Stmt-While]");
    $$->add_son($3);
    $$->add_son($5);
    $$->set_type(STMT_WHILE);
  }
  | LVal ASSIGN Exp SEMI { /*赋值语句*/
    $$ = new StmtNode("[Stmt-Assign]");
    $$->add_son($1);
    $$->add_son($3);
    $$->set_type(STMT_ASSIGN);
  }
  | Block {
    $$ = new StmtNode("[Stmt-Block]");
    $$->add_son($1);
    $$->set_type(STMT_BLOCK);
  }
  | Exp SEMI {
    $$ = new StmtNode("[Stmt-Exp]");
    $$->add_son($1);
    $$->set_type(STMT_EXP);
  }
  | SEMI {
    $$ = new StmtNode("[Stmt-None]");
    $$->set_type(STMT_NONE);
  }
  ;

Decl
  : ConstDecl {
    // $$ = new DeclNode("[Decl]");
    $$ = $1;
    $$->set_const_decl(true);
  }
  | VarDecl {
    // $$ = new DeclNode("[Decl]");
    $$ = $1;
    $$->set_const_decl(false);
  }
  ;

ConstDecl
  : CONST BType ConstDefList SEMI {
    $$ = new DeclNode("[ConstDecl]");
    $$->add_son($2);
    $$->add_son(cur_deflist);
  }
  ;

ConstDefList
  : ConstDef {
    cur_deflist = new DefListNode("[ConstDefList]");
    cur_deflist->add_son($1);
  }
  | ConstDefList COMMA ConstDef {
    cur_deflist->add_son($3);
  }
  ;

ConstDef
  : IDENT DimList ASSIGN InitVal {
    $$ = new DefNode("[ConstDef]");
    $$->add_son($1->c_str());
    $$->add_son(cur_dimlist);
    $$->add_son($4);
    dimlist_stack.pop();
    if(!dimlist_stack.empty()) cur_dimlist = dimlist_stack.top();
    else cur_dimlist = nullptr;
  }
  ;

VarDecl
  : BType VarDefList SEMI {
    $$ = new DeclNode("[VarDecl]");
    $$->add_son($1);
    $$->add_son(cur_deflist);
  }
  ;

VarDefList
  : VarDef {
    cur_deflist = new DefListNode("[VarDefList]");
    cur_deflist->add_son($1);
  }
  | VarDefList COMMA VarDef {
    cur_deflist->add_son($3);
  }
  ;

VarDef
  : IDENT DimList {
    $$ = new DefNode("[Vardef]");
    $$->add_son($1->c_str());
    $$->add_son(cur_dimlist);
    dimlist_stack.pop();
    if(!dimlist_stack.empty()) cur_dimlist = dimlist_stack.top();
    else cur_dimlist = nullptr;
  }
  | IDENT DimList ASSIGN InitVal {
    $$ = new DefNode("[Vardef]");
    $$->add_son($1->c_str());
    $$->add_son(cur_dimlist);
    $$->add_son($4);
    dimlist_stack.pop();
    if(!dimlist_stack.empty()) cur_dimlist = dimlist_stack.top();
    else cur_dimlist = nullptr;
  }
  ;

InitValList
  : {
    cur_initvallist = new InitValListNode("[InitValList]");
    initvallist_stack.push(cur_initvallist);
  }
  | InitVal {
    cur_initvallist = new InitValListNode("[InitValList]");
    initvallist_stack.push(cur_initvallist);
    cur_initvallist->add_son($1);
  }
  | InitValList COMMA InitVal {
    cur_initvallist->add_son($3);
  }
  ;

InitVal
  : Exp {
    $$ = new InitValNode("[InitVal-Exp]");
    $$->add_son($1);
  }
  | LCURLY InitValList RCURLY {
    $$ = new InitValNode("[InitVal-List]");
    $$->add_son(cur_initvallist);
    initvallist_stack.pop();
    if(!initvallist_stack.empty()) cur_initvallist = initvallist_stack.top();
  }
  ;

DimList
  : {
    cur_dimlist = new DimListNode("[DimList]");
    dimlist_stack.push(cur_dimlist);
  }
  | DimList Dim {
    cur_dimlist->add_son($2);
  }
  ;

Dim
  : LSQBRAC Number RSQBRAC {
    $$ = new DimNode("[Dim]");
    $$->add_son($2);
  }
  ;

Exp
  : AddExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  ;

AddExp
  : MulExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | AddExp ADD MulExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_ADD));
    $$->add_son($3);
  }
  | AddExp SUB MulExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_SUB));
    $$->add_son($3);
  }
  ;

MulExp
  : UnaryExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | MulExp MUL UnaryExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_MUL));
    $$->add_son($3);
  }
  | MulExp DIV UnaryExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_DIV));
    $$->add_son($3);
  }
  | MulExp MOD UnaryExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_MOD));
    $$->add_son($3);
  }
  ;

UnaryExp
  : PrimaryExp {
    $$ = new ExpNode("[UnaryExp]");
    $$->add_son($1);
  }
  | IDENT LBRACE FuncRParams RBRACE {
    $$ = new ExpNode("[UnaryExp]");
    CallFuncNode *call = new CallFuncNode("[call]");
    call->add_son($1->c_str());
    call->add_son(cur_funcrparams);
    $$->add_son(call);
    funcrparams_stack.pop();
    if(!funcrparams_stack.empty()) cur_funcrparams = funcrparams_stack.top();
  }
  | UnaryOp UnaryExp {
    $$ = new ExpNode("[UnayExp]");
    $$->add_son($1);
    $$->add_son($2);
  }
  ;


PrimaryExp
  : LBRACE Exp RBRACE {
    $$ = new ExpNode("[PrimaryExp]");
    PrimaryExpNode *prim = new PrimaryExpNode("[PrimExp]");
    prim->add_son($2);
    $$->add_son(prim);
  }
  | LVal {
    $$ = new ExpNode("[PrimaryExp]");
    $$->add_son($1);
  }
  | Number {
    $$ = new ExpNode("[PrimaryExp]");
    $$->add_son($1);
  }
  ;

LVal
  : IDENT DimList {
    $$ = new LValNode("LVal");
    $$->add_son($1->c_str());
    $$->add_son(cur_dimlist);
    dimlist_stack.pop();
    if(!dimlist_stack.empty()) cur_dimlist = dimlist_stack.top();
    else cur_dimlist = nullptr;
  }
  ;

FuncRParams
  : {
    cout<<"void r params"<<endl;
    cur_funcrparams = new AstNode("[FuncRParams]");
    funcrparams_stack.push(cur_funcrparams);
  }
  | Exp {
    cout<<"single r param"<<endl;
    cur_funcrparams = new AstNode("[FuncRParams]");
    cur_funcrparams->add_son($1);
    funcrparams_stack.push(cur_funcrparams);
  }
  | FuncRParams COMMA Exp {
    cout<<"recursive r params"<<endl;
    cur_funcrparams->add_son($3);
  }
  ;

UnaryOp
  : ADD {
    $$ = new OpNode(AST_ADD);
  }
  | SUB {
    $$ = new OpNode(AST_SUB);
  }
  | NOT {
    $$ = new OpNode(AST_NOT);
  }
  ;

Cond
  : LOrExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  ;

LOrExp
  : LAndExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | LOrExp OR LAndExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_OR));
    $$->add_son($3);
  }
  ;

LAndExp
  : EqExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | LAndExp AND EqExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_AND));
    $$->add_son($3);
  }
  ;

EqExp
  : RelExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | EqExp EQUAL RelExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_EQ));
    $$->add_son($3);
  }
  | EqExp NEQUAL RelExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_NEQ));
    $$->add_son($3);
  }
  ;

RelExp
  : AddExp  {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
  }
  | RelExp GT AddExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_GT));
    $$->add_son($3);
  }
  | RelExp LT AddExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_LT));
    $$->add_son($3);
  }
  | RelExp GTEQ AddExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_GTEQ));
    $$->add_son($3);
  }
  | RelExp LTEQ AddExp {
    $$ = new ExpNode("[Exp]");
    $$->add_son($1);
    $$->add_son(new OpNode(AST_LTEQ));
    $$->add_son($3);
  }
  ;

Number
  : INT_CONST {
    $$ = new NumberNode("[Number]");
    $$->set_int($1);
  }
  | FLOAT_CONST {
    $$ = new NumberNode("[Number]");
    $$->set_float($1);
  }
  ;

BType
  : INT {
    $$ = new TypeNode("[BType]");
    $$->set_type(AST_INT);
  }
  | FLOAT {
    $$ = new TypeNode("[BType]");
    $$->set_type(AST_FLOAT);
  }
  ;

%%

void yyerror(const char *s) {
  cerr << "error: " << s << endl;
}
