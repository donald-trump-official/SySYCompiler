%option noyywrap
%option nounput
%option noinput

%{
#include <cstdlib>
#include <string>
#include "parser.hpp"

using namespace std;
%}

/* 空白符和注释 */
WhiteSpace		[ \t\n\r]*
LineComment		"//".*$
BlockComment	"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"

/* 标识符 */
Identifier		[a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
Decimal			[1-9][0-9]*
Octal			0[0-7]*
Hexadecimal		0[xX][0-9a-fA-F]+
Float			[0-9]*\.[0-9]+

%%
{WhiteSpace}	{}
{LineComment}	{ printf("lexer: find line comment\n"); }
{BlockComment}	{ printf("find block comment\n"); }

"int"			{ return INT; }
"float"			{ return FLOAT; }
"void"			{ return VOID; }

"if"			{ return IF; }
"else"			{ return ELSE; }
"while"			{ return WHILE; }
"break"			{ return BREAK; }
"continue"		{ return CONTINUE; }
"return"        { return RETURN; }
"const"			{ return CONST; }

"("				{ return LBRACE; }
")"				{ return RBRACE; }
"["				{ return LSQBRAC; }
"]"				{ return RSQBRAC; }
"{"				{ return LCURLY; }
"}"				{ return RCURLY; }
";"				{ return SEMI; }
","				{ return COMMA; }

"+"				{ return ADD; }
"-"				{ return SUB; }
"*"				{ return MUL; }
"/"				{ return DIV; }
"%"				{ return MOD; }

"="				{ return ASSIGN; }

"=="			{ return EQUAL; }
"!="			{ return NEQUAL; }
">"				{ return GT; }
"<"				{ return LT; }
">="			{ return GTEQ; }
"<="			{ return LTEQ; }

"||"			{ return OR; }
"&&"			{ return AND; }
"!"				{ return NOT; }

{Identifier}    { yylval.str_val = new string(yytext); return IDENT; }

{Decimal}       { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Octal}         { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Hexadecimal}   { yylval.int_val = strtol(yytext, nullptr, 0); return INT_CONST; }
{Float}			{ yylval.float_val = strtof(yytext, nullptr); return FLOAT_CONST; }

.               { return yytext[0]; }
%%
