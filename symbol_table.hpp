#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;

//address offset
int offset = 0;

class attr{

	public:
		int val;
		int offset;
		string type;
		int width;
		int reg;

		attr(int val, int offset, string type, int width){
			this->val = val;
			this->offset = offset;
			this->type = type;
			this->width = width;
			this->reg = -1;
		}

		void print(){
			cout<<"( ";
			cout<<this->val<<", ";
			cout<<this->offset<<", ";
			cout<<this->type<<", ";
			cout<<this->width<<", ";
			cout<<this->reg<<" ";
			cout<<")\n";
		}
};

class Scope {

	public:

		unordered_map<string, attr*> table;
		Scope *prev;

		Scope(Scope *p){
			prev = p;
		}
	
		void put(string s, attr *a){
			table.insert({s,a});
		}

		attr* get(string s){
			for( Scope *scp = this; scp!=NULL; scp = scp->prev){
				auto found = (scp->table).find(s);
				if(found!=table.end()) return found->second;
			}
			return NULL;
		}

		void print(){
			for(auto iter = table.begin(); iter != table.end(); iter++){
				cout<<iter->first<<" : ";
				iter->second->print();
			}
			cout<<endl<<endl;
		}

		string printData(){
			string code = "";
			vector<int> data(offset/4);
			for(auto iter = table.begin(); iter != table.end(); iter++){
				data[((iter->second)->offset)/4] = (iter->second)->val;
			}
			for(int i = 0;i<offset/4;i++){
				code += to_string(data[i]) + " ";
			}
			return code;
		}
};

//stack to keep track of the hierarchical symbol table	
stack <Scope*> symref;
	
//global symbol table
Scope* top = new Scope(NULL);

//attributes
attr* a;