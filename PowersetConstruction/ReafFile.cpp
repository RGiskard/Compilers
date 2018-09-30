#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
using namespace std;

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
	// Fill DataNumbers
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
		for(auto it=Entradas.begin();it!=Entradas.end();it++)
			cout<<*it<<" ";
		cout<<endl << line<< '\n';	
		//}
		//myfile.close();
	}
	else cout << "Unable to open file"; 
	
	
	//for(auto it=elementos.begin();it!=elementos.end();it++)
	//	cout<<*it<<" ";
	return 0;
}
