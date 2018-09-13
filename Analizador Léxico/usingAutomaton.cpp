#include <iostream>
#include <map>
#include <string> 
#include <vector>
#include <algorithm>

using namespace std;
typedef string  _str;
typedef vector<string> vector_str;
typedef map<int,map<char,int>>  Tabela;
vector_str tokenizer(_str & flujo);
bool isNumber(_str);
bool isVariable(_str);
bool isVariableDiagram(_str);
namespace utilitarios
{
	
	inline vector_str gramatica(){
		vector_str gram;
		gram.push_back("+");
		gram.push_back("-");
		gram.push_back("*");
		gram.push_back("/");
		gram.push_back("%");
		gram.push_back("^");
		gram.push_back("(");
		gram.push_back(")");
		gram.push_back("=");
		gram.push_back(">");
		gram.push_back(" ");
		gram.push_back(";");
		return gram;
	}
	inline Tabela TablaTransition()
	{
		/*Tabla de transicion 0*/
		
		//llenando a tabela
		//mensaje de error 0
		
		Tabela Tabla;
		Tabla[1]['d']=2;Tabla[1]['.']=0;Tabla[1]['E']=0;Tabla[1]['+']=0;Tabla[1]['-']=0;
		Tabla[2]['d']=2;Tabla[2]['.']=3;Tabla[2]['E']=5;Tabla[2]['+']=0;Tabla[2]['-']=0;
		Tabla[3]['d']=4;Tabla[3]['.']=0;Tabla[3]['E']=0;Tabla[3]['+']=0;Tabla[3]['-']=0;
		Tabla[4]['d']=4;Tabla[4]['.']=0;Tabla[4]['E']=5;Tabla[4]['+']=0;Tabla[4]['-']=0;
		Tabla[5]['d']=7;Tabla[5]['.']=0;Tabla[5]['E']=0;Tabla[5]['+']=6;Tabla[5]['-']=6;
		Tabla[6]['d']=7;Tabla[6]['.']=0;Tabla[6]['E']=0;Tabla[6]['+']=0;Tabla[6]['-']=0;
		Tabla[7]['d']=7;Tabla[7]['.']=0;Tabla[7]['E']=0;Tabla[7]['+']=0;Tabla[7]['-']=0;
		return Tabla;
	}
	inline Tabela TablaTransitionVariable()
	{
		Tabela Tabla;
		Tabla[1]['l']=3;Tabla[1]['d']=2;
		Tabla[2]['l']=0;Tabla[2]['d']=0;
		Tabla[3]['l']=3;Tabla[3]['d']=3;
		return Tabla;
	}
	inline char getEntradaDigit(char d)
	{
		char value='F';//Fallo caracter de error 
		if(isdigit(d))
			value= 'd';
		if(d=='E')
			value= 'E';
		if(d=='.')
			value= '.';
		if(d=='+')
			value= '+';
		if(d=='-')
			value= '-';
		return value;
	}
	inline char getEntradaAlpha(char letra)
	{
		char value='F';//Fallo caracter de error 
		if(isalpha(letra))
			value= 'l';
		if(isdigit(letra))
			value= 'd';
		return value;
	}
	
	inline map<_str,_str> keywords(){
		map<_str,_str> words;
		words["int"]="Keyword [INT]";
		words["if"]="Keyword [IF]";
		words["while"]="Keyword [WHILE]";
		words["="]="AS [=]";
		words["*"]="Mul [*]";
		return words;
	}
}	

void testear(){
	map<_str,_str> kWords=utilitarios::keywords();
	_str stream("if2=5+9.7;");
	vector_str V=tokenizer(stream);
	for(auto it=V.begin();it!=V.end();++it)
	{
		if(*it=="int"||*it=="if"||*it=="while"||*it=="="||*it=="*")
			cout<<kWords[*it]<<endl;
		else
		{
			if(isVariableDiagram(*it))
				cout<<*it<<" TOKEN [ID]"<<endl;
			else
			{
				if(isNumber(*it))
					cout<<*it<<" TOKEN [NUM]"<<endl;
			}	
		}
	}
		//cout<<*it<<endl;
}

int main(int argc, char *argv[]) {
	

	/*_str flujo="int a=5.5E;";
	vector_str V=tokenizer(flujo);
	for(auto it=V.begin();it!=V.end();++it)
		cout<<*it<<endl;
	cout<<"Tamanio "<<V.size()<<endl;*/
	//_str number("123.4");
	//_str variable("112.ABB");
	cout<<isNumber(number)<<endl;
	//cout<<isVariable(variable)<<endl;
	//cout<<isVariableDiagram(variable)<<endl;
	
	//testear();
	return 0;
}

vector_str tokenizer(_str & flujo)
{
	/*
	Dada una gramatica o tabla de simbolos, la siguiente porcion de la funcion tokenizer
	permitira discrimiar entre numero o simbolo y separara el flujo de carracteres en tokens que
	tengan un significado.
	*/
	vector_str salida;
	//tabla de simbolos
	auto gram=utilitarios::gramatica();
	_str buffer("");
	_str key("");
	vector_str::iterator it2;
	for(auto it=flujo.begin();it!=flujo.end();it++)
	{
		key+=*it;
		it2=find(gram.begin(),gram.end(),key);
		if(it2==gram.end())
			buffer+=*it;
		else
		{
			salida.push_back(buffer);
			buffer="";
			if((*it2).size()==1)
				salida.push_back(*it2);
		}
		key="";
	}
	if(buffer!="")
		salida.push_back(buffer);
	/*
	Esta seccion se encargara de eliminar los tokens muertos o ""
	*/
	vector_str::iterator seekerSpace;
	string space="";
	seekerSpace=find(salida.begin(),salida.end(),space);
	while(seekerSpace!=salida.end())
	{
		salida.erase(seekerSpace);
		seekerSpace=find(salida.begin(),salida.end(),space);
	}
	/*
	Esta seccion del codigo analiza cada token procesado, si hay un "-" asociado a un numero los juntar como
	un \'unico token.
	*/
	vector_str temp;
	vector_str::iterator iterador=salida.begin();
	while(iterador!=salida.end())
	{
		_str fuzor("");
		vector_str::iterator tmpIzquierda,tmpDerecha,previus,next;
		previus=iterador;
		next=iterador;
		if(previus!=salida.begin())
			previus--;
		next++;
		if(next==salida.end())
			next--;
		tmpIzquierda=find(gram.begin(),gram.end(),*previus);
		tmpDerecha=find(gram.begin(),gram.end(),*next);
		if(*iterador=="-")
		{
			if(tmpIzquierda!=gram.end())
			{
				fuzor+=*iterador;
				fuzor+=*next;
				temp.push_back(fuzor);
				iterador++;
				iterador++;
			}
		}
		if(iterador!=salida.end())
		{
			temp.push_back(*iterador);
			iterador++;
		}
	}
	salida=temp;
	return salida;
}



bool isNumber(_str flujo)
{
	Tabela Tabla=utilitarios::TablaTransition();
	char c;
	int estado=1;
	auto it=flujo.begin();
	c=*it;
	while(it!=flujo.end())
	{
		char Entrada=utilitarios::getEntradaDigit(c);
		//cout<<"valor: "<<c<<" Entrada: "<<Entrada<<endl;
		estado=Tabla[estado][Entrada];
		//cout<<"El estado es:"<<estado<<endl;
		if(estado==0)
			return false;
		it++;
		c=*it;
	}	
	return true;
}	

bool isVariable(_str flujo)
{
	Tabela Tabla=utilitarios::TablaTransitionVariable();
	char c;
	int estado=1;
	auto it=flujo.begin();
	c=*it;
	while(it!=flujo.end())
	{
		char Entrada=utilitarios::getEntradaAlpha(c);
		//cout<<"valor: "<<c<<" Entrada: "<<Entrada<<endl;
		estado=Tabla[estado][Entrada];
		//cout<<"El estado es:"<<estado<<endl;
		if(estado==0)
			return false;
		it++;
		c=*it;
	}	
	return true;
}

bool isVariableDiagram(_str flujo)
{
	char symbol;
	int estado=1;
	auto it=flujo.begin();
	symbol=*it;
	while(it!=flujo.end())
	{
		switch(estado)
		{
		case 1:
		{
			if(isalpha(symbol))
				estado=3;
			else
			{
				if(isdigit(symbol))
					estado=2;
				else
					return false;
			}	
		}
		break;
		case 2:
			return false; break;
		case 3:
		{
			if(isalpha(symbol))
				estado=3;
			else
			{
				if(isdigit(symbol))
					estado=3;
				else
					return false;
			}	
		}
		break;
		}	
		
		it++;
		symbol=*it;
	}	
	if(estado!=3)
		return false;
	else
		return true;
}
