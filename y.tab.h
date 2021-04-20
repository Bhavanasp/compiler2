/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INIT = 258,
    INT = 259,
    FLOAT = 260,
    CHAR = 261,
    VOID = 262,
    INTCONST = 263,
    FLOATCONST = 264,
    CHARCONST = 265,
    TRUE = 266,
    FALSE = 267,
    ID = 268,
    COMMA = 269,
    SCOL = 270,
    IF = 271,
    ELSE = 272,
    LOOP = 273,
    BREAK = 274,
    RETURN = 275,
    PRINT = 276,
    ASSGN = 277,
    PLUS = 278,
    MINUS = 279,
    MUL = 280,
    DIV = 281,
    LES = 282,
    LEQ = 283,
    GRE = 284,
    GEQ = 285,
    EQL = 286,
    NEQ = 287,
    AND = 288,
    OR = 289,
    NOT = 290,
    LSBR = 291,
    RSBR = 292,
    LPBR = 293,
    RPBR = 294,
    LFBR = 295,
    RFBR = 296,
    ERR = 297,
    UMINUS = 298,
    BRAC = 299
  };
#endif
/* Tokens.  */
#define INIT 258
#define INT 259
#define FLOAT 260
#define CHAR 261
#define VOID 262
#define INTCONST 263
#define FLOATCONST 264
#define CHARCONST 265
#define TRUE 266
#define FALSE 267
#define ID 268
#define COMMA 269
#define SCOL 270
#define IF 271
#define ELSE 272
#define LOOP 273
#define BREAK 274
#define RETURN 275
#define PRINT 276
#define ASSGN 277
#define PLUS 278
#define MINUS 279
#define MUL 280
#define DIV 281
#define LES 282
#define LEQ 283
#define GRE 284
#define GEQ 285
#define EQL 286
#define NEQ 287
#define AND 288
#define OR 289
#define NOT 290
#define LSBR 291
#define RSBR 292
#define LPBR 293
#define RPBR 294
#define LFBR 295
#define RFBR 296
#define ERR 297
#define UMINUS 298
#define BRAC 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "parser.y" /* yacc.c:1909  */

	int ival;
	float fval; 
	char text[20];

	class Node* node;
	class Stmts* stmts;
	class Stmt* stmt;
	class AssgnStmt* assgn_stmt;
	class Expression* expr;
	class UnaryExpr* unary_expr;
	class BinaryExpr* binary_expr;
	class ConstExpr* const_expr;
	class Loc* loc;
	class PrintStmt* print_stmt;

#line 159 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
