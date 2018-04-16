#include <stdio.h>
#include <string.h>
#include <ctype.h>
int count, flag;
char expr[20];
void E();
void T();
void E_();
void T_();
void check();

int main(int argc, char const *argv[])
{
	count = 0;
	flag = 0;

	printf("Enter the expression: ");
	scanf("%s", expr);

	E();

	if ((strlen(expr) == count) && flag == 0)
	{
		printf("VALID\n");
	}
	else{
		printf("INVALID\n");
	}
	return 0;
}

void E(){
	T();
	E_();
}

void E_(){
	if (expr[count] == '+')
	{
		count++;
		T();
		E_();
	}
}

void T(){
	check();
	T_();
}

void check(){
	if (isalnum(expr[count]))
	{
		count++;
	}
	else if (expr[count] == '(')
	{
		count++;
		E();
		if (expr[count] == ')')
		{
			count++;
		}
		else{
			flag = 1;
		}
	}
	else{
		flag = 1;
	}
}

void T_(){
	if (expr[count] == '*')
	{
		count++;
		check();
		T_();
	}
}