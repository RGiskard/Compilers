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

set<int> Eclausura(set<int> R,set<int> S,Tabela Transiciones){
	//Pila 
	stack<int> Pila;
	set<int> clausura (R); 
	set<int>::iterator iter;
	//Apilamos todos los estados de R
	for(iter=R.begin(); iter!=R.end();++iter) 
		Pila.push(*iter);
	while(!Pila.empty())
	{
		int actual=Pila.top();
		Pila.pop();
		cout<<actual<<endl;
		for(iter=S.begin(); iter!=S.end();++iter)
			if(Transiciones[actual][*iter]==-1)
				if(find(R.begin(),R.end(),*iter)==R.end())
				{
					R.insert(*iter);
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
	
	
	vector<int> v;
	vector<int> r;
	v.push_back(1);v.push_back(2);v.push_back(3);v.push_back(4);v.push_back(5);v.push_back(6);v.push_back(6);
	r.push_back(1);r.push_back(6);
	set<int> R(r.begin(), r.end());
	set<int> estados(v.begin(), v.end());
	set<int>::iterator iter;
	
	Eclausura(R,estados,trans);
	
	return 0;
}

