%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

extern int yylex();
void yyerror(char *msg);
%}

%union
{
	int val;
}
%token NUM
%left '+' '-'
%left '*' '/'
%left '~' '^'
%type <val> E
%type <val> NUM

%%
S 	: E 			{printf("%d", $1);}
E 	: E '+' E 		{$$ = $1 + $3;}
	| E '-' E 		{$$ = $1 - $3;}
	| E '*' E 		{$$ = $1 * $3;}
	| E '/' E 		{
					if($3 == 0){
						printf("Divide by zero error");
						exit(0);
					}
					else{
					$$ = $1 / $3;
					}
					}
	| '-' E 		{$$ = -$2;}
	| '~' E			{$$ = sqrt($2);}
	| E '^' E 		{$$ = pow($1, $3);}
	| '(' E ')'		{$$ = $2;}
	| NUM			{$$ = $1;}
	;
%%

void yyerror(char *msg){
	fprintf(stderr, "%s", msg);
}
int main (void){
	return yyparse();
}