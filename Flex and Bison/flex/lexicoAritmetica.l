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
OPEPLUS [+]
OPMINUS [-]
OPDIV [/]
OPTIMES [*]

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
{OPEPLUS}	{printf("Operador Suma %s\n",yytext);}
{OPMINUS}	{printf("Operador Menos %s\n",yytext);}
{OPDIV}	{printf("Operador Division %s\n",yytext);}
{OPTIMES}	{printf("Operador Multiplicación %s\n",yytext);}
{DELIMITADOR}   {}
.               {printf("ERROR LEXICO\n");}


%%
