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

void match(char expectedToken)
{
	if(token==expectedToken)
		token=getchar();
	else
		error();
}

int main(int argc, char *argv[]) {
	
	int result;
	token=getchar();
	result=exp();
	if(token=='\n')
		printf("Result =%d\n",result);
	else
		error();
	return 0;
}

int exp()
{
	int temp=term();
	while((token=='+')||(token=='-'))
	{
		switch(token){
		case '+': match('+');
			temp+=term();
			break;
		case '-': match('-');
			temp-=term();
			break;
		}
	}
	return temp;
}

int term()
{
	int temp=factor();
	while(token=='*')
	{
		match('*');
		temp*=factor();
	}
	return temp;
}

int factor()
{
	int temp;
	if(token=='(')
	{
		match('(');
		temp=exp();
		match(')');
	}
	else if(isdigit(token))
	{
		ungetc(token,stdin);
		scanf("%d",&temp);
		token=getchar();
	}
	else error();
	return temp;
}
