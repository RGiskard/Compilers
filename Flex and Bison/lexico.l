%{
# include <cerrno>
#include <stdio.h>
#include <string>
#include "driver.h"
#include "parser.tab.hh"
#undef yywrap
#define yywrap() 1
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput
%option outfile="scanner.cpp"
DIGITO [0-9]
LETRA [a-zA-ZñÑ]

NUMERO {DIGITO}+("."{DIGITO}+)?
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO}|"_")*

DELIMITADOR [\t\r\f" "]
%%
{NUMERO}        {return yy::calculadora_parser::make_NUMERO(strtol (yytext, NULL, 10),loc);}
{IDENTIFICADOR}	{return yy::calculadora_parser::make_IDENTIFICADOR(yytext,loc);}
"+"		{return yy::calculadora_parser::make_MAS(loc);}
"-"		{return yy::calculadora_parser::make_MENOS(loc);}
"*"		{return yy::calculadora_parser::make_POR(loc);}
"/"		{return yy::calculadora_parser::make_DIVISION(loc);}

{DELIMITADOR}   {}
.               {printf("ERROR LEXICO %s\n",yytext);}
<<EOF>>		{return yy::calculadora_parser::make_FIN(loc);}
%%
void calculadora_driver::iniciarScanner()
{
  yy_flex_debug = false;
  if(file.empty() || file == "-"){
    printf("No se encuentra el archivo de entrada");
    exit(1);
  }else{
    yyin = fopen (file.c_str (), "r");
  }
}
void calculadora_driver::terminarScanner()
{
  fclose(yyin);
}