%{
	#include "y.tab.h"
%}

alpha	[a-zA-Z]
digit	[0-9]
digits	{digit}+

%%

"init"				{return INIT;}
"int"				{strcpy(yylval.text,yytext); return INT;}
"float"				{strcpy(yylval.text,yytext); return FLOAT;}
"char"				{strcpy(yylval.text,yytext); return CHAR;}
"void"				{return VOID;}
","				{strcpy(yylval.text,yytext); return COMMA;}
";"				{strcpy(yylval.text,yytext); return SCOL;}
"loop"				{return LOOP;}
"if"				{return IF;}
"else"				{return ELSE;}
"break"				{return BREAK;}
"return"			{return RETURN;}
"print"				{return PRINT;}
"="				{strcpy(yylval.text,yytext); return ASSGN;}
"+"				{strcpy(yylval.text,yytext); return PLUS;}
"-"				{strcpy(yylval.text,yytext); return MINUS;}
"*"				{strcpy(yylval.text,yytext); return MUL;}
"/"				{strcpy(yylval.text,yytext); return DIV;}
"<"				{strcpy(yylval.text,yytext); return LES;}
"<="				{strcpy(yylval.text,yytext); return LEQ;}
">"				{strcpy(yylval.text,yytext); return GRE;}
">="				{strcpy(yylval.text,yytext); return GEQ;}
"=="				{strcpy(yylval.text,yytext); return EQL;}
"!="				{strcpy(yylval.text,yytext); return NEQ;}
"&&"				{strcpy(yylval.text,yytext); return AND;}
"||"				{strcpy(yylval.text,yytext); return OR;}
"!"				{strcpy(yylval.text,yytext); return NOT;}
"["				{return LSBR;}
"]"				{return RSBR;}
"("				{return LPBR;}
")"				{return RPBR;}
"{"				{return LFBR;}
"}"				{return RFBR;}
{alpha}({alpha}|{digit})*	{strcpy(yylval.text,yytext); return ID;}
("+"|"-")?{digits}		{yylval.ival = atoi(yytext); return INTCONST;}
("+"|"-")?{digits}"."{digits}	{yylval.fval = atof(yytext); return FLOATCONST;}
"'"{alpha}"'"			{strcpy(yylval.text,yytext); return CHARCONST;}
"true"					{strcpy(yylval.text,yytext); return TRUE;}
"false"					{strcpy(yylval.text,yytext); return FALSE;}
[ \t\n]				;
"$"				{return 0;}
.  				{return ERR;}

%%



