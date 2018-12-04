/**************************************************/
/* Ejemplo de YAcc con una accion semántica       */
/*                                                */
/*    S -> x S ¦ A B c                            */
/*    A -> a                                      */
/*    B -> b                                      */
/**************************************************/

%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
%}

%token ID  /* no utilizado */

%%
  S: 'x' { printf(" token x \n"); }  S ;
  S: A  B 'c' ;
  A: 'a' ;
  B: 'b' ;
%%

yylex()   /* analizador lexico  */
{ 
  int c;  
  do  c=getchar(); while (c==' '|| c=='\t');
  if (c=='\n') return EOF;  /* fin de archivo para yylex */
  if (isalpha(c))
         return c;
  yyerror("caracter ilegal");
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
    }
}

