%{
#include "y.tab.h"
%}

%%
[0-9]+ 	{
			yylval.val = atoi(yytext);
			return NUM;
		}
[+\-*/^~()]	{
			return yytext[0];
		}
[\t]	{
		;
		}
[\n]	{
		return 0;
		}
%%
