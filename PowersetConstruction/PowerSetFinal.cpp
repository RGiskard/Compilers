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
struct Automata
{
	set<int> inicial;
	set<int> entradas;
	set<int> estados;
	Tabela tablaSvsS;
	TabelaState tablaSvsE;
	set<int> aceptores;
	Automata(set<int> i,set<int>e,set<int>es,Tabela T,TabelaState TT,set<int> a)
		:inicial(i),entradas(e),estados(es),tablaSvsS(T),tablaSvsE(TT),aceptores(a)
	{
	}
};
template<typename T>
void printSet(set<T> conjunto,ostream& os)
{
	os<<"{";
	for(auto it=conjunto.begin();it!=conjunto.end();it++)
		os<<*it<<" ";
	os<<"}"<<endl;
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

bool marcas(map<set<int>,bool> mapa,set<int> &R)
{
	for(auto it=mapa.begin();it!=mapa.end();it++)
	{	
		if(!(*it).second)
		{
			R=(*it).first;
			return false;
		}
	}
	return true;
}

void PowersetConstruction(Automata afnd,ostream & os)
{
	set<int> R;
	set<int> UU;
	map<set<int>,bool> mapa;
	map<set<int>,map<int,set<int>>> nTransiciones;
	set<set<int>> D_est;
	D_est.insert(Eclausura(afnd.inicial,afnd.estados,afnd.tablaSvsS));
	mapa[Eclausura(afnd.inicial,afnd.estados,afnd.tablaSvsS)]=false;
	while(!marcas(mapa,R))
	{
		mapa[R]=true;
		for(auto it=afnd.entradas.begin();it!=afnd.entradas.end();it++)
		{
			UU=Eclausura(Mover(R,*it,afnd.tablaSvsE),afnd.estados,afnd.tablaSvsS);
			if(find(D_est.begin(),D_est.end(),UU)==D_est.end())
			{
				D_est.insert(UU);
				mapa[UU]=false;
			}	
			nTransiciones[R][*it]=UU;
		}
		
	}
	int i=0;
	map<set<int>,int> Asociar;
	os<<"Estados "<<endl;
	for(auto it=mapa.begin();it!=mapa.end();it++)
	{	
		os<<i<<"= ";
		printSet((*it).first,os);
		Asociar[(*it).first]=i;
		i++;
	}
	os<<"Estados de Aceptacion"<<endl;
	//buscar Estado de aceptación:
	os<<"4"<<endl;
	os<<"Transiciones de estado (z,y,z)"<<endl;
	for(auto iter=D_est.begin();iter!=D_est.end();iter++)
	{
		for(auto it=afnd.entradas.begin();it!=afnd.entradas.end();it++)
			os<<Asociar[*iter]<<" "<<*it<<" "<<Asociar[nTransiciones[*iter][*it]]<<endl; 
	}
}	

void execute(const char *entrada,const char *salida)
{
	string line;
	ifstream myfile (entrada);
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
		//printSet(Mover(S0,0,tranState),cout);
		myfile.close();
		Automata afnd(S0,Sigma,S,trans,tranState,T);
		ofstream ofs(salida);
		PowersetConstruction(afnd,ofs);
		
	}
	else cout << "No se pudo abrir el archivo"; 
}

int main (int argc, char *argv[]) {
	
	//execute("entrada.txt","salida.txt");
	//return 0;	
	if (argc==1)
	{
		printf("Debes ingresar mas parametros...\n");
		return 1;
	}
	execute(argv[1],argv[2]);
	return 0;
}
