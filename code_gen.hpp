#include "symbol_table.hpp"

extern string asmcode;

//REGISTER DESCRIPTOR - code start

#define SIZE 3

int reg_to_free = 8;

vector<vector<attr*>> regdesc(SIZE);

string space(){
	return "       ";
}

void init(){
	for(int i = 0;i<SIZE;i++){
		vector<attr*> locs;
		regdesc[i] = locs;
	}
}

int getReg(attr* a, bool load){
	if(a->reg!=-1) return a->reg;
	reg_to_free++;
	if(reg_to_free==9+SIZE){
		reg_to_free = 9;
	}
	for(int i = 0;i<SIZE;i++){
		if(regdesc[i].empty()){
			a->reg = i+9;
			regdesc[i].push_back(a);
			if(load) asmcode += space()+"lw $"+to_string(a->reg)+", "+to_string(a->offset)+"($8)"+"\n";
			return a->reg;
		};
	}
	for(auto iter = regdesc[reg_to_free-9].begin(); iter != regdesc[reg_to_free-9].end(); iter++){
		asmcode += space()+"sw $"+to_string(reg_to_free)+", "+to_string((*iter)->offset)+"($8)"+"\n";
		(*iter)->reg = -1;
	}
	regdesc[reg_to_free-9].clear();
	a->reg = reg_to_free;
	regdesc[reg_to_free-9].push_back(a);
	if(load) asmcode += space()+"lw $"+to_string(a->reg)+", "+to_string(a->offset)+"($8)"+"\n";
	return reg_to_free;
}

void storeData(){
	for(int reg = 0; reg<SIZE; reg++){
		for(auto iter = regdesc[reg].begin(); iter != regdesc[reg].end(); iter++){
			asmcode += space()+"sw $"+to_string(reg+9)+", "+to_string((*iter)->offset)+"($8)"+"\n";
			(*iter)->reg = -1;
		}
	}
}

string printDataSeg(){
	return top->printData();
}

void printMipsCode(){
	asmcode  =  string(".data\n			.word	")
		+ printDataSeg() + string("\n")
		+ string(".text")+ string("\n")
		+ string(".globl main") + string("\n\n")
		+ asmcode;
 	cout<<asmcode;
 }

//REGISTER DESCRIPTOR - code end
