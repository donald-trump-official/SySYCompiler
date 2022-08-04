/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_MNT_C_USERS_CMBGZ_DOCUMENTS_SYSYCOMPILER_BUILD_PARSER_HPP_INCLUDED
# define YY_YY_MNT_C_USERS_CMBGZ_DOCUMENTS_SYSYCOMPILER_BUILD_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/mnt/c/Users/CMBGZ/Documents/SySYCompiler/src/Front/parser.y"

  #include <memory>
  #include <string>
  #include "ast.hpp"

#line 54 "/mnt/c/Users/CMBGZ/Documents/SySYCompiler/build/parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CONST = 260,
    VOID = 261,
    RETURN = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    BREAK = 266,
    CONTINUE = 267,
    ADD = 268,
    SUB = 269,
    MUL = 270,
    DIV = 271,
    MOD = 272,
    ASSIGN = 273,
    EQUAL = 274,
    NEQUAL = 275,
    GT = 276,
    LT = 277,
    GTEQ = 278,
    LTEQ = 279,
    AND = 280,
    OR = 281,
    NOT = 282,
    LCURLY = 283,
    RCURLY = 284,
    LSQBRAC = 285,
    RSQBRAC = 286,
    LBRACE = 287,
    RBRACE = 288,
    SEMI = 289,
    COMMA = 290,
    IDENT = 291,
    INT_CONST = 292,
    FLOAT_CONST = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "/mnt/c/Users/CMBGZ/Documents/SySYCompiler/src/Front/parser.y"

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

#line 127 "/mnt/c/Users/CMBGZ/Documents/SySYCompiler/build/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MNT_C_USERS_CMBGZ_DOCUMENTS_SYSYCOMPILER_BUILD_PARSER_HPP_INCLUDED  */
