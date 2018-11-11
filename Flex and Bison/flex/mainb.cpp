#include <FlexLexer.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
        ifstream in("in");
        yyFlexLexer* lexer = new yyFlexLexer(&in);
	while(lexer->yylex() != 0)
		;
	return 0;
}
