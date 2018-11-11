%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%option c++
%option outfile="ScannerAritmetica.cpp"
%option case-insensitive
%option noyywrap

DIGITO [0-9]
LETRA [a-zA-ZñÑ]
PARENTESISI [(]
PARENTESISD [)]


ENTERO {DIGITO}+
REAL {DIGITO}+"."{DIGITO}+
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO}|"_")*

DELIMITADOR [\t\r\f" "]

%%

{ENTERO}        {printf("Numero Entero %s\n",yytext);}
{REAL}          {printf("Numero Real   %s\n",yytext);}
{IDENTIFICADOR}	{printf("Identificador %s\n",yytext);}
{PARENTESISI}	{printf("Parentesis izquierdo %s\n",yytext);}
{PARENTESISD}	{printf("Parentesis Derecho %s\n",yytext);}
{DELIMITADOR}   {}
.               {printf("ERROR LEXICO");}


%%
