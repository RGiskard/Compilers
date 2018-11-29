%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
%}

%%
S:'x' S;
S:A B 'c';
A:'a';
B:'b';
%%
yylex() /*analizador lexico*/
{
	int c;
	do c=getchar();while(c==' '||c=='\t');
	if(c=='\n') return EOF;/*Fin de archivo*/
	if(isalpha(c))
		return c;
	yyerror("Caracter Ilegal");
}
yyerror(char *m) /*funcion de yacc para el error*/
{
	printf("%s",m);
	exit(0);
}

main()
{
	while(1)
	{
		yyparse(); /*analizador sintactico*/
	}
}
