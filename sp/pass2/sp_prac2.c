#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int tokencnt;
char buffer[80],token1[20],token2[20],token3[20],token4[20],token5[20],token6[20];
typedef struct symbol{
        int addr;
        char name[10];
        int opcode;
}sot;
typedef struct literal{
        int lit_id;
        int lit_addr;
        char lit_val;
}lot;

sot s[10];
lot l[10];
int scnt=0,lcnt=0;


int searchLOT(int index)
{
        int i;
        for(i = 0;i < lcnt;i++)
        {
               if(l[i].lit_id == index)
		{
			return l[i].lit_addr;
		} 
        }
        return -1;
}

int searchSOT(int index)
{
	int i;
	for(i = 0;i < scnt;i++)
	{
		if(s[i].opcode == index)
		{
			return s[i].addr;
		}
	}	
	return -1;
}

int main()
{
	int i = 0,j,k,cnt;
	FILE *fp,*fp1,*fp2,*fp3;
	fp = fopen("intermediate.txt","r");
	fp1 = fopen("literal.txt","r");
	fp2 = fopen("symbol.txt","r");
	fp3 = fopen("machinecode.txt","w");
	
	while(fgets(buffer,80,fp1))
	{
		strcpy(token1,"");
		strcpy(token2,"");
		strcpy(token3,"");
		sscanf(buffer,"%s%s%s",token1,token2,token3);
		l[lcnt].lit_id = atoi(token1);
        	l[lcnt].lit_addr = atoi(token2);
        	l[lcnt].lit_val = token3[0];
        	lcnt++;
	}
	while(fgets(buffer,80,fp2))
	{
		strcpy(token1,"");
		strcpy(token2,"");
		strcpy(token3,"");
		sscanf(buffer,"%s%s%s",token1,token2,token3);
		s[scnt].addr = atoi(token3);
        	strcpy(s[scnt].name,token2);
        	s[scnt].opcode = atoi(token1);
        	scnt++;
	}
	printf("lcnt=%d scnt=%d\n",lcnt,scnt);
	
	while(fgets(buffer,80,fp))
	{
		j = 0;
		strcpy(token1,"");
		strcpy(token2,"");
		strcpy(token3,"");
		strcpy(token4,"");
		strcpy(token5,"");
		strcpy(token6,"");
		tokencnt = sscanf(buffer,"%s%s%s%s%s%s",token1,token2,token3,token4,token5,token6);
		if(tokencnt == 6)
		{
			int l2 = strlen(token2);
			int l5 = strlen(token5);
			token2[l2-1] = '\0';
			token5[l5-1] = '\0';
			char sc = token4[1];
			int index = atoi(token5);
			if(sc == 'S')
			{
				j = searchSOT(index);
			}
			else if(sc == 'L')
			{
				j = searchLOT(index);
			}
			printf("%s\t%s\t%d\t%s\n",token2,token3,j,token6);
			fprintf(fp3,"%s\t%s\t%d\t%s\n",token2,token3,j,token6);
				
		}
	}
	
	return 0;
}
