#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <cstdlib> 

int preanalisis;
//declaración de funciones
void parea(int);
void error();
void Resto();
void Term();

void Exp()
{
	if(isdigit(preanalisis))
	{
		Term();
		Resto();
	}
	else
		error();	   
}
void Resto()
{
	if(preanalisis=='+')
	{
		parea('+');
		Term();
		printf("+");
		Resto();
	}
	else 
	{
		if(preanalisis=='-')
		{
			parea('-');
			Term();
			printf("-");
			Resto();
		}
		else;//cadena vacia \
		   
	}
}

void Term()
{
	if(isdigit(preanalisis))
	{
		printf("%c",preanalisis);
		//putchar(preanalisis)
		parea(preanalisis);	
	}
	else
		error();	   
}
void error()
{
	printf("Error de sintaxis");
}
void parea(int t)
{
	if(preanalisis==t)
		preanalisis=getchar();
	else
		error();
}

int main() {
	
	//clrscr();
	system("cls");
	preanalisis=getchar();
	Exp();
	getch();
}

