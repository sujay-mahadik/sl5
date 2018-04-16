#include <stdio.h>
#include <string.h>

FILE *fp;

typedef struct 
{
	char name[10];
	int id;
} couple;

typedef struct
{
	char name[10];
	char type[20];
	int id;	
} tuple;


tuple UST[50];
int UST_size = 0;

char *keywords[30] = {"void", "int", "float"};
char *operators[30] = {"+", "-","=", ",", "."};
char *terminals[30] = {";", "(", ")", "{", "}"};

int is_keyword(char *key){
	int i;
	for (i = 0; i < 2; i++)
	{
		if (strcmp(key, keywords[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int is_operator(char *key){
	int i;
	for (i = 0; i < 4; i++)
	{
		if (strcmp(key, operators[i]) == 0)
		{	
			return 1;
			
		}
	}
	return 0;
}
int is_terminal(char *key){
	int i;
	for (i = 0; i < 4; i++)
	{
		if (strcmp(key, terminals[i]) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int is_literal(char *key){
	int len = strlen(key);
	if (((key[0] == '\'' && key[len -1] == '\'')) && len > 1 )
	{
		return 1;
	}
	return 0;
}

void insert(char *key){
	if (strlen(key) == 0)
	{
		return;
	}
	if (is_keyword(key))
	{
		strcpy(UST[UST_size].name, key);
		strcpy(UST[UST_size].type, "KEYWORD");
		UST[UST_size].id = UST_size;
		UST_size++;
	}
	else if (is_terminal(key))
	{
		strcpy(UST[UST_size].name, key);
		strcpy(UST[UST_size].type, "TERMINAL");
		UST[UST_size].id = UST_size;
		UST_size++;
	}
	else if(is_operator(key))
	{
		strcpy(UST[UST_size].name, key);
		strcpy(UST[UST_size].type, "OPERATOR");
		UST[UST_size].id = UST_size;
		UST_size++;
	}
	else if(is_literal(key))
	{
		strcpy(UST[UST_size].name, key);
		strcpy(UST[UST_size].type, "LITERAL");
		UST[UST_size].id = UST_size;
		UST_size++;
	}
	else
	{
		strcpy(UST[UST_size].name, key);
		strcpy(UST[UST_size].type, "IDENTIFIER");
		UST[UST_size].id = UST_size;
		UST_size++;
	}
}

void read(){
	char temp [30];
	int temp_size = 0;

	while(!feof(fp)){
		char ch = fgetc(fp);
		char buff[2];
		buff[0] = ch;
		buff[1] = '\0';

		while((ch != ' ' && ch != '\n' && ch != '\t') && !feof(fp)){
			if (is_operator(buff) || is_terminal(buff))
			{
				temp[temp_size] = '\0';
				insert(temp);
				insert(buff);

				temp[0] = '\0';
				temp_size = 0;
				break;
			}
			if (is_literal(temp))
			{
				insert(temp);
				temp[0] = '\0';
				temp_size = 0;
			}
			temp[temp_size] = ch;
			temp[temp_size + 1] ='\0';
			temp_size++;

			ch = fgetc(fp);
		}
		temp[temp_size] = '\0';
		insert(temp);
		temp_size = 0;
	}
}
 void display(){
 	int i;
 	for(i = 0; i < UST_size -1; i++){
 		printf("id = %d \t\t name = %s \t\t\t type = %s\n", UST[i].id, UST[i].name, UST[i].type );
 	}
 }
int main(int argc, char const *argv[])
{
	fp = fopen("input.txt", "r");
	if(fp)
		printf("file opend\n");
	read();
	display();

	fclose(fp);
	return 0;
}