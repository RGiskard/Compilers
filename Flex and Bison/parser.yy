%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {calculadora_parser}
%define api.token.constructor
%define api.namespace {yy}
%define api.value.type variant
%define parse.assert
%code requires
{
#include <string>
#include <stdio.h>
class calculadora_driver;
}
%param { calculadora_driver& driver }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include "driver.h"
#include <iostream>
}
%define api.token.prefix {TOK_}

//Listadode Terminales
%token MAS "+"
%token MENOS "-"
%token POR "*"
%token DIVISION "/"
%token <std::string> IDENTIFICADOR "id"
%token <float> NUMERO "num"
%token FIN 0 "eof"

//Listado de No Terminales
%type <float> E
%type <float> T
%type <float> F

%printer { yyoutput << $$; } <*>;
%%
%start INICIO;

INICIO : E;

E : E "+" T
   |E "-" T
   |T;

T : T "*" F
   |T "/" F
   |F;
   
F : "num";
%%
void yy::calculadora_parser::error(const location_type& lugar, const std::string& lexema)
{
  std::cout << "Error Sintactico " << lexema << std::endl;
}