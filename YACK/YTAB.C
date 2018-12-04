#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 14 "sint01.y"

short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 5
# define YYLAST 24
short yyact[]={

   4,   8,   7,   1,   6,   3,   5,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   2 };
short yypact[]={

 -97,-1000, -97, -96,-1000,-1000, -98,-1000,-1000 };
short yypgo[]={

   0,   3,   5,   4 };
