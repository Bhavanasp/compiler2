%{
	#include "ast_nodes.hpp"

	using namespace std;

	extern FILE* yyin;

	int yylex();
	int yyerror(string s);
	int size(string s);

	string temp(int val);

	int tempvar = 0;
%}

%union {
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
}

%token INIT
%token INT FLOAT CHAR VOID
%token INTCONST FLOATCONST CHARCONST
%token TRUE FALSE
%token ID
%token COMMA SCOL
%token IF ELSE
%token LOOP
%token BREAK
%token RETURN
%token PRINT
%token ASSGN
%token PLUS MINUS MUL DIV
%token LES LEQ GRE GEQ EQL NEQ
%token AND OR NOT
%token LSBR RSBR
%token LPBR RPBR
%token LFBR RFBR
%token ERR

%left ASSGN
%left OR
%left AND
%left EQL NEQ
%left LES LEQ
%left GEQ GRE
%left PLUS MINUS
%left MUL DIV
%right NOT
%right UMINUS
%left BRAC

%type <loc> loc
%type <text> ID
%type <ival> INTCONST
%type <expr> expr
%type <text> ASSGN OR AND EQL NEQ LES LEQ GEQ GRE PLUS MINUS MUL DIV NOT
%type <stmts> stmts
%type <stmt> stmt

%%

start		:	prog

				{
					//top->print();
				}

prog		:	INIT 

				{
					asmcode += "main:\n";
					asmcode +=  space()+string("lui $8, 0x1001")+"\n";
				}

				LFBR stmts RFBR

				{
					storeData();
					asmcode += space()+"jr $ra";
				}

stmts		:	stmt stmts

				{
					$$ = new Stmts($1, $2);
				}

			|	{	$$ = NULL; }

			;

stmt		:	INT ID SCOL

				{
					int width = size("int");
					a = new attr(0, offset, "int", width);
					top->put($2, a);
					offset = offset+size("int");
				}

			|	loc ASSGN expr SCOL

				{
					$$ = new AssgnStmt($1, $3);
				}

			|	PRINT LPBR loc RPBR SCOL

				{
					$$ = new PrintStmt($3);
				}

			;


/*bool 		:	bool OR bool

			|	bool AND bool

			|	NOT bool

			|	expr EQL expr

			|	expr GRE expr

			|	expr GEQ expr

			|	expr LES expr

			|	expr LEQ expr

			|	TRUE

			|	FALSE

			;
*/

expr		:	expr PLUS expr

				{
					$$ = new BinaryExpr(temp(0), a, $2, $1, $3);
				}

			|	expr MINUS expr

				{
					$$ = new BinaryExpr(temp(0), a, $2, $1, $3);
				}

			|	expr MUL expr

				{
					$$ = new BinaryExpr(temp(0), a, $2, $1, $3);
				}

			|	expr DIV expr

				{
					$$ = new BinaryExpr(temp(0), a, $2, $1, $3);
				}

			|	LPBR expr RPBR %prec BRAC

				{
					$$ = $2;
				}

			|	MINUS expr %prec UMINUS

				{
					$$ = new UnaryExpr(temp(0), a, $1, $2);
				}

			|	loc

				{
					$$ = $1;
				}

			|	INTCONST

				{	
					$$ = new ConstExpr(temp($1), a);
				}

			;

loc			:	ID

				{
					a = top->get($1);
					$$ = new Loc($1,a);
				}

			;

%%

int main(int argc, char *argv[]){
	if(argc != 2)
	{
		cout<<"Usage: <exefile> <inputfile>"<<endl;;
       	exit(0);
	}
	yyin = fopen(argv[1], "r");
	init();
	yyparse();
	printMipsCode();
	return 0;
}

int yyerror(string s){
	cout<<"Error: "<<s<<endl;;
	return 0;
}

int size(string s){	if(s=="int"){
		return 4;
	}
	else if(s=="float"){
		return 4;
	}
	else if(s=="char"){
		return 1;
	}
	else {
		return 0;
	}
}

string temp(int val){
	tempvar++;
	string temperory = "#" + to_string(tempvar);
	int width = size("int");
	a = new attr(val, offset, "int", width);
	top->put(temperory, a);
	offset = offset+size("int");
	return temperory;
}