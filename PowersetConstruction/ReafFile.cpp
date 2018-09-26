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

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	cout<<"Aqui estoy causa"<<endl;
	return elems;
}



int main () {
	string line;
	ifstream myfile ("test.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
	
	vector<string> elementos=split(line,' ');
	cout<<elementos.size()<<endl;
	for(auto it=elementos.begin();it!=elementos.end();it++)
		cout<<*it<<" ";
	return 0;
}
