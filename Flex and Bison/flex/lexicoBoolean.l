%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%option c++
%option outfile="ScannerBoolean.cpp"
%option case-insensitive
%option noyywrap

SIMBOLO [0-1]
DIGITO	[0-9]
LETRA [a-zA-ZñÑ]
PARENTESISI [(]
PARENTESISD [)]
NOT [~]
AND [*]
OR  [+]



IDENTIFICADOR {LETRA}({LETRA}|{DIGITO}|"_")*

DELIMITADOR [\t\r\f" "]

%%

{SIMBOLO}       {printf("Símbolo %s\n",yytext);}
{IDENTIFICADOR}	{printf("Identificador %s\n",yytext);}
{PARENTESISI}	{printf("Parentesis izquierdo %s\n",yytext);}
{PARENTESISD}	{printf("Parentesis Derecho %s\n",yytext);}
{NOT}		{printf("Operador Negate %s\n",yytext);}
{AND}		{printf("Operador conjunction %s\n",yytext);}
{OR}		{printf("Operador disjunction %s\n",yytext);}
{DELIMITADOR}   {}
.               {printf("ERROR LEXICO\n");}


%%
