#include <iostream>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#define NUM 256
#define AS '='
#define MAS '+'
#define MENOS '-'
#define POR '*'
#define DIV '/'
#define PCOMA ';'
#define MAYOR '>'
#define FLUJO 'F'
int Scanner();
void Mostrar(int);
using namespace std;
FILE *f;
char lexema[80];
int main(int argc, char *argv[]) {
	int token;
	f=stdin;
	if(argc==2)
	{
		f=fopen(argv[1],"rt");
		if(f==NULL)
			f=stdin;
	}
	if(f==stdin)
	{
		printf("Ingrese Texto .......... termine con Ctrl z \n");
	}
	while(1)
	{
		token=Scanner();
		if(token==EOF)
			break;
		Mostrar(token);
	}
	if(f!=stdin)
		fclose(f);  
	return 0;
}

int Scanner()
{
	int c;
	int i;
	do{ 
		c=fgetc(f);
	} while(isspace(c));//ignorar espacios en blanco
	if(c==EOF)
		return EOF;
	
	if(c!='+'&&c!='-'&&c!='*'&&c!='/'&&c!='>'&&c!='='&&c!=';')
	{
		if(isdigit(c))//Regla de NUM
		{
			bool value=true;
			i=0;
			do{
				lexema[i++]=c;
				c=fgetc(f);
				if(isalpha(c)){
					value=false;
					cout<<"ERROR"<<endl;
					//exit(0);
				}
			} while(isdigit(c));
			lexema[i]=0;
			ungetc(c,f);
			if(value)
				return NUM;
			else
				return 10;
		}
		if(isalnum(c))
		{
			i=0;
			do{
				lexema[i++]=c;
				c=fgetc(f);
			} while(isalnum(c));
			lexema[i]=0;
			ungetc(c,f);
			return FLUJO;
		}	
	}
	else
	{		   
		if(c=='=')//Asignacion
		{
			lexema[0]=c;
			lexema[1]=0;
			return AS;
		}
		
		if(c=='+')//MAS
		{
			lexema[0]=c;
			lexema[1]=0;
			return MAS;
		}
		if(c=='-')//MAS
		{
			lexema[0]=c;
			lexema[1]=0;
			return MENOS;
		}
		if(c=='*')//MAS
		{
			lexema[0]=c;
			lexema[1]=0;
			return POR;
		}
		if(c=='/')//MAS
		{
			lexema[0]=c;
			lexema[1]=0;
			return DIV;
		}
		
		if(c==';')//Punto y Coma
		{
			lexema[0]=c;
			lexema[1]=0;
			return PCOMA;
		}
		
		if(c=='>')//Mayor
		{
			lexema[0]=c;
			lexema[1]=0;
			return MAYOR;
		}
	}
}

void Mostrar(int token)
{
	switch(token)
	{
	case 10:cout<<"Error"<<endl;	
	case NUM: printf("Token = NUM [%s]\n",lexema);break;
	case AS: printf("Token = AS [%c]\n",token);break;
	case MAS:printf("Token = MAS [%c]\n",token);break;
	case MENOS:printf("Token = MENOS [%c]\n",token);break;
	case POR:printf("Token = POR [%c]\n",token);break;
	case DIV:printf("Token = DIV [%c]\n",token);break;
	case PCOMA: printf("Token = PCOMA [%c]\n",token);break;
	case MAYOR: printf("Token = PCOMA [%c]\n",token);break;
	case FLUJO: 
		{
			int casos=0;
			if(strcmp(lexema,"IF")==0)casos=1;	
					
			if(strcmp(lexema,"WHILE")==0)casos=2;
				
			if(strcmp(lexema,"ELSE")==0)casos=3;
			switch(casos){
				case 0: {printf("Token = ID [%s]\n",lexema);break;}
				case 1: {printf("Token = KEYWORD [%s]\n",lexema); break;}
				case 2: {printf("Token = KEYWORD [%s]\n",lexema);break;}
				case 3:	{printf("Token = KEYWORD [%s]\n",lexema);break;}}
			
		}
		break;
	}
}

