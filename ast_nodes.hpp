#include "code_gen.hpp"

string asmcode = "";

//AST NODES - code start

//Node

class Node{
public:
	string igcode;
	string asmlycode;
};

//Expressions section

class Expression : public Node{
public:
	string exprtype;
	string id;
	attr* a;
};

//Location (identifier)

class Loc : public Expression{
public:
	Loc(string id, attr* a){
		this->id = id;
		this->a = a;
		this->exprtype = "LocExpr";
	}
};

//Constant Expression

class ConstExpr : public Expression{
public:
	void igGen(){
		this->igcode = this->id + " = " + to_string(this->a->val); 
	}
	void asmGen(){
		getReg(this->a, true);
	}
	ConstExpr(string id, attr* a){
		this->id = id;
		this->a = a;
		this->exprtype = "ConstExpr";
		//this->igGen();
		this->asmGen();
	}
};

//Unary Expression

class UnaryExpr : public Expression{
public:
	string op;
	Expression* expr;

	void igGen(){
		this->igcode = this->id + " = " + op + " " + expr->id;
	}

	void asmGen(){
		int currReg1 = getReg(this->a, false);
		int currReg2 = getReg(expr->a, true);
		this->asmlycode += space()+"sub $"+to_string(currReg1)+", $0"+", $"+to_string(currReg2)+"\n";
		asmcode += this->asmlycode;
	}

	UnaryExpr(string id, attr* a, string op, Expression* expr){
		this->id = id;
		this->a = a;
		this->op = op;
		this->expr = expr;
		this->exprtype = "UnaryExpr";
		this->igGen();
		this->asmGen();
	}
};

//Binary Expression

class BinaryExpr : public Expression{
public:
	string op;
	Expression* expr1;
	Expression* expr2;

	void igGen(){
		this->igcode = this->id + " = " + expr1->id + " " + op + " " + expr2->id;
	}

	void asmGen(){
		int currReg1 = getReg(this->a, false);
		int currReg2 = getReg(expr1->a, true);
		int currReg3 = getReg(expr2->a, true);

		if(op=="+") op = "add";
		else if(op=="-") op = "sub";
		else if(op=="*") op = "mul";
		else if(op=="/") op = "div";

		this->asmlycode += space()+op+" $"+to_string(currReg1)+", $"+to_string(currReg2)+", $"+to_string(currReg3)+"\n";

		asmcode += this->asmlycode;
	}

	BinaryExpr(string id, attr* a, string op, Expression* expr1, Expression* expr2){
		this->id = id;
		this->a = a;
		this->op = op;
		this->expr1 = expr1;
		this->expr2 = expr2;
		this->exprtype = "BinaryExpr";	
		this->igGen();
		this->asmGen();
	}
};

//Statement

class Stmt : public Node{};

//Statements

class Stmts : public Node{
public:
	Stmt* stmt;
	Stmts* stmts;
	Stmts(Stmt* stmt, Stmts* stmts){
		this->stmt = stmt;
		this->stmts = stmts;
	}
};

//Assignment Statements

class AssgnStmt : public Stmt{
public:
	Loc* loc;
	Expression* expr;

	void igGen(){
		this->igcode = loc->id+" = "+expr->id;
	}

	void asmGen(){
		int currReg1 = getReg(loc->a, false);
		int currReg2 = getReg(expr->a, true);
		this->asmlycode += space()+"move $"+to_string(currReg1)+", $"+to_string(currReg2)+"\n";

		asmcode += this->asmlycode;
	}
	AssgnStmt(Loc* loc, Expression* expr){
		this->loc = loc;
		this->expr = expr;
		this->igGen();
		this->asmGen();
	}
};

//Print Statement

class PrintStmt : public Stmt{
public:
	Loc* loc;

	void igGen(){
		this->igcode = "print " + loc->id;
	}

	void asmGen(){
		this->asmlycode += space()+"li $v0, 1"+"\n";
		this->asmlycode += space()+"move $a0, $"+to_string(getReg(loc->a, true))+"\n";
		this->asmlycode += space()+"syscall"+"\n";

		asmcode += this->asmlycode;
	}
	PrintStmt(Loc* loc){
		this->loc = loc;
		this->igGen();
		this->asmGen();
	}
};

//AST NODES - code end