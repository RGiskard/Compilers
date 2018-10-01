#include <fstream>
#include <sstream>
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
/*Imprimir conjuntos*/
template<typename T>
void printSet(set<T> conjunto,ostream& os)
{
	os<<"{";
	for(auto it=conjunto.begin();it!=conjunto.end();it++)
		os<<*it<<" ";
	os<<"}";
}	

/*Union de conjuntos*/
template<typename T>
set<T> U(set<T> A,set<T> B){
	set<T> unir(A);
	for(auto it=B.begin();it!=B.end();it++)
		unir.insert(*it);
	return unir;
}	

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
//conjunto,entrada,tabla
set<int> Mover(set<int> R,int u,TabelaState states)
{
	set<int> move;
	for(auto it=R.begin();it!=R.end();it++)
		move=U(move,states[*it][u]);
	return move;
}	

vector<string> &split(const string &s, char delim,vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length()>0)
			elems.push_back(item);  
	return elems;
}

vector<int> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	// llenado  DataNumbers
	vector<int> intNumbers;
	for (unsigned int i=0; i<elems.size(); i++)
	{
		int num = atoi(elems.at(i).c_str());
		intNumbers.push_back(num);
	}
	return intNumbers;
}



int main () {
	string line;
	ifstream myfile ("entrada.txt");
	if (myfile.is_open())
	{
		//while ( getline (myfile,line) )
		//{
		
		getline (myfile,line);//Primera parte del contenido a no considerar;
		getline (myfile,line);//Estados
		int totalEstados=atoi(line.c_str());
		getline (myfile,line);//Estados
		vector<int> estados=split(line,' ');
		getline (myfile,line);//segunda parte del contenido a no considerar;
		getline (myfile,line);//Estados de aceptacion
		int totalEstadosAceptacion=atoi(line.c_str());
		getline (myfile,line);
		vector<int> aceptores=split(line,' ');
		getline (myfile,line);//tercera parte del contenido a no considerar;
		getline (myfile,line);//Total Entradas
		int totalEntradas=atoi(line.c_str());
		getline (myfile,line);//Total Entradas
		vector<int> Entradas=split(line,' ');
		getline (myfile,line);//Cuarta parte del contenido a no considerar;
		getline (myfile,line);
		int totalTransiciones=atoi(line.c_str());
		//cout<<endl << ++totalTransiciones<< '\n';	
		//LLenado Tablas de Transicion y Tabla de estados
		vector<int> tempTransition;
		Tabela trans;
		TabelaState tranState;
		for(int i=0;i<totalTransiciones;i++)
		{
			getline (myfile,line);
			tempTransition=split(line,' ');
			//LLenado Tabla de transicion
			trans[tempTransition[0]][tempTransition[2]]=tempTransition[1];
			(tranState[tempTransition[0]][tempTransition[1]]).insert(tempTransition[2]);
			//cout<<line<<endl;
		}
		getline(myfile,line);//Estado incial
		getline(myfile,line);
		//Estado inicial
		set<int> S0;
		S0.insert((atoi(line.c_str()))); 
		set<int> S(estados.begin(),estados.end());
		//Alfabeto
		set<int> Sigma(Entradas.begin(),Entradas.end());
		//estados de aceptacion
		set<int> T(aceptores.begin(),aceptores.end());
		
		//printSet(Eclausura(S0,S,trans),cout);
		printSet(Mover(S0,0,tranState),cout);
		myfile.close();
	}
	else cout << "Unable to open file"; 
	
	
	//for(auto it=elementos.begin();it!=elementos.end();it++)
	//	cout<<*it<<" ";
	return 0;
}
