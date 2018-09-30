#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
typedef map<int,map<int,int>> Tabela;
typedef map<int,map<int,set<int>>> TabelaState;

set<int> Eclausura(set<int> R,set<int> S,Tabela Transiciones){
	//Pila 
	stack<int> Pila;
	set<int> clausura (R); 
	set<int>::iterator iter;
	//Apilamos todos los estados de R
	for(iter=clausura.begin(); iter!=clausura.end();++iter) 
		Pila.push(*iter);
	while(!Pila.empty())
	{
		int actual=Pila.top();
		Pila.pop();
		for(iter=S.begin(); iter!=S.end();++iter)
			if(Transiciones[actual][*iter]==-1)
				if(find(clausura.begin(),clausura.end(),*iter)==clausura.end())
				{
					clausura.insert(*iter);
					Pila.push(*iter);
				}	
		
	}
	return clausura;
}

int main(int argc, char *argv[]) {
	//Tabla de transicion
	Tabela trans;
	trans[1][2]=-1;trans[1][5]=-1;
	trans[2][3]=-1;
	trans[3][4]=1;
	trans[5][6]=0;
	trans[6][1]=1;
	//Tabla Estado vs Entrada
	TabelaState tranState;
	tranState[1][-1]=set<int>();
	(tranState[1][-1]).insert(2);
	(tranState[1][-1]).insert(5);
	cout<<"-----"<<endl;
	for(auto it=(tranState[1][-1]).begin();it!=(tranState[1][-1]).end();it++)
		cout<<" "<<*it<<endl;
	cout<<"------"<<endl;
	vector<int> v;
	vector<int> r;
	v.push_back(1);v.push_back(2);v.push_back(3);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(6);
	r.push_back(1);r.push_back(6);
	set<int> R(r.begin(), r.end());
	set<int> estados(v.begin(), v.end());
	set<int>::iterator iter;
	set<int> clausura;
	clausura=Eclausura(R,estados,trans);
	for(auto it=clausura.begin();it!=clausura.end();it++)
		cout<<*it<<" ";
	cout<<endl;  
	cout<<clausura.size()<<endl;
	return 0;
}

