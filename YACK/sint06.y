/**************************************************/
/* Ejemplo en Yacc de una calculadora simple      */
/*                                                */
/*    prg -> exp                                  */
/*    exp -> exp  + term   | exp - term  | term   */
/*   term -> term * factor | factor               */ 
/* factor -> ( exp ) | num                        */
/*                                                */
/* Pruebe con la entradas:                        */
/*    w = 1+12+(4-21-(5+(3)))-8                   */
/*    w = 2+8*(2-6)                               */
/**************************************************/


%{

#include <stdio.h>
#include <ctype.h>
#include <math.h>


%}


%token num
%left '+' '-'  /* + y - son asociativos por la izquierda */
%left '*'

%%

prg      :  exp  { printf("%d\n",$1); };

exp      :  exp '+' term   { $$=$1 + $3; }
         |  exp '-' term   { $$=$1 - $3; }
         |  term           { $$=$1;};

term     :  term '*' factor { $$=$1 * $3; }
         |  factor         { $$=$1;};

factor   :  '(' exp ')'    { $$=$2;}
         |  num            { $$=$1;};

%%


yylex()   /* analizador lexico  */
{ 
  int c;  

  do  c=getchar(); while (c==' '|| c=='\t');
  
  if (c=='\n') return EOF;  /* fin de archivo para yylex */

  if (isdigit(c))  /* regla de NUM */
  {
     ungetc(c,stdin);
     scanf("%d",&yylval);  /* yylval contiene el lexema del token NUM */
     return(num);
  }

  return c;

}

yyerror(char *m)   /* funcion de yacc para error */
{ 

  printf("%s",m); 
  exit(0); 
}


main()  
{  
    clrscr();

    while(1)
    { 
       yyparse();  /* analizador sintactico */
       printf("\n"); 
    }
}
