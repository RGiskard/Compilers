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
void printSet(set<T> conjunto)
{
	cout<<"{";
	for(auto it=conjunto.begin();it!=conjunto.end();it++)
		cout<<*it<<",";
	cout<<"}";
}	

/*Union de conjuntos*/
template<typename T>
set<T> U(set<T> A,set<T> B){
	set<T> unir(A);
	for(auto it=B.begin();it!=B.end();it++)
		unir.insert(*it);
	return unir;
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
		for(auto it=trans.begin();it!=trans.end();it++);
		//cout<<tranState.size()<<endl;
		

		printSet(U(tranState[3][-1],tranState[6][-1]));
		myfile.close();
	}
	else cout << "Unable to open file"; 
	
	
	//for(auto it=elementos.begin();it!=elementos.end();it++)
	//	cout<<*it<<" ";
	return 0;
}
