#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
char token;
/*Prototipos de función*/
int exp();
int term();
int factor();
int error()
{
	fprintf(stderr,"Error\n");
	exit(1);
}
int main(int argc, char *argv[]) {
	
	return 0;
}

