#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int tokencnt;
char buffer[80],token1[20],token2[20],token3[20],token4[20];
char *pot[] = {"START","END","ORIGIN","EQU","LTORG"};
char *mot[] = {"MOVER","STOP","MOVEM","READ","PRINT","ADD","SUB","MULT"};
char *dltab[] = {"DC","DS","DB"};
char *regtab[] = {"AREG","BREG","CREG","DREG"};
int lenPOT = 5;
int lenMOT = 7;
int lenDTB = 3;
int pooltab[4];
int lenROT = 4;
int lenpool = 0;
int LC;
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
int lcnt = 0;
int scnt = 0;
sot s[10];
lot l[10];
int searchPOT(char token1[20])
{
	int i = 0;
	for(i = 0;i < lenPOT;i++)
	{
		if((strcmp(token1,pot[i]) == 0))
		{
			return i;
		}
	}	
	return -1;
}
int searchMOT(char token1[20])
{
	int i = 0;
	for(i = 0;i < lenMOT;i++)
	{
		if((strcmp(token1,mot[i]) == 0))
		{
			return i;
		}
	}	
	return -1;
}
int searchSOT(char token2[20])
{
	int i = 0;
	for(i = 0;i < scnt;i++)
	{
		if((strcmp(token2,s[i].name) == 0))
		{
			return i;
		}
	}	
	return -1;
}
int searchDLTAB(char token2[20])
{
	int i = 0;
	for(i = 0;i < lenDTB;i++)
	{
		if((strcmp(token2,dltab[i]) == 0))
		{
			return i;
		}
	}	
	return -1;
}
int searchROT(char token2[20])
{
	int i = 0;
	for(i = 0;i < lenROT;i++)
	{
		if((strcmp(token2,regtab[i]) == 0))
		{
			return i;
		}
	}	
	return -1;
}
int searchLOT(char token3,int cnt)
{
        int i = 0;
        for(i = cnt;i < lcnt;i++)
        {
               if(l[i].lit_val== token3)
		{
			return i;
		} 
        }
        return -1;
}
int main()
{
	int i = 0,j,k,cnt;
	FILE *fp,*fp1,*fp2,*fp3;
	fp = fopen("input.txt","r");
	fp1 = fopen("intermediate.txt","w");
	fp2 = fopen("symbol.txt","w");
	fp3 = fopen("literal.txt","w");
	while(fgets(buffer,80,fp))
	{
		j = 0;
		strcpy(token1,"");
		strcpy(token2,"");
		strcpy(token3,"");
		strcpy(token4,"");
		tokencnt = sscanf(buffer,"%s%s%s%s",token1,token2,token3,token4);
		switch(tokencnt)
		{
			case 1:	j = searchPOT(token1);
				if(j != -1)
				{
					fprintf(fp1,"(AD, %d)\n",j);
					if((strcmp(token1,"LTORG") == 0) || (strcmp(token1,"END") == 0))
					{
					        pooltab[lenpool] = lcnt;
					        lenpool++;
					        for(i = pooltab[lenpool - 2];i < pooltab[lenpool-1];i++)
					        {
					        	LC = LC + 1;
					        	l[i].lit_addr = LC;
					        }
					}
					else if(strcmp(token1,"START") == 0)
					{
					        pooltab[lenpool] = 0;
					        lenpool++;
					        LC = 0;
				        }
				 }
				else
				{
					j = searchMOT(token1);
					if(j != -1)
					{
						fprintf(fp1,"(IS, %d)\t\t%d\n",j,LC);
						LC = LC + 1;
					}
					else
					{
						printf("Invalid Neumonic\n");
					}
				}
			break;
			case 2: j = searchPOT(token1);
				if(j != -1)
				{
					int LC = atoi(token2);
					fprintf(fp1,"(AD, %d) - (C, %d)\n",j,LC);
					break;
				}
				j = searchMOT(token1);
				if(j != -1)
				{
					i = searchSOT(token2);
					if(i != -1)
                                        {
                                             fprintf(fp1,"(IS, %d) - (S, %d)\t\t%d\n",j,s[i].opcode,LC);
                                             LC = LC + 1;   					
                                        }
                                        else
                                        {
                                                s[scnt].opcode = scnt;
                                                strcpy(s[scnt].name,token2);
                                                s[scnt].addr = 0;
                                                fprintf(fp1,"(IS, %d) - (S, %d)\t\t%d\n",j,s[scnt].opcode,LC);
                                                LC = LC + 1;
                                                scnt++;  
                                        }
				}

			break;
		        case 3: j = searchMOT(token1);
		                if(j != -1)
		                {
		                        i = searchROT(token2);
		                        if(i != -1)
		                        {
		                                if(token3[0] != '=')
		                                {
		                                     k = searchSOT(token3);
					                if(k != -1)
                                                        {
                                                             LC = LC + 1;
						fprintf(fp1,"(IS, %d) %d (S, %d)\t\t%d\n",j,i,s[k].opcode,LC);			
                                                        }
                                                        else
                                                        {
                                                        	LC = LC + 1;
                                                        	s[scnt].opcode = scnt;
                                                             	strcpy(s[scnt].name,token3);
                                                            	s[scnt].addr = 0;  
                                                            	scnt++;
                                                	fprintf(fp1,"(IS, %d) %d (S, %d)\t\t%d\n",j,i,s[scnt-1].opcode,LC);
                                                        }
   
		                                }
		                                else
		                                {
		                                        cnt = pooltab[lenpool-1];
		                                        k = searchLOT(token3[1],cnt);
		                                        if(k != -1)
		                                        {
		                                                printf("Duplicate token\n");
		                                        }
		                                        else
		                                        { 
		                                               l[lcnt].lit_id = lcnt;
		                                               l[lcnt].lit_val = token3[1];    
		                                               l[lcnt].lit_addr = 0;
		                                               LC = LC + 1;
		                                               fprintf(fp1,"(IS, %d) %d (L, %d)\t\t%d\n",j,i,l[lcnt].lit_id,LC);
		                                               lcnt++;     
		                                        }
		                                }               
		                        }
		                }
		                else
		                {	
		                	j = searchSOT(token1);
		                	if(j != -1)
		                	{
		                		i = searchDLTAB(token2);
		                		if(i != -1)
		                		{
		                			LC = LC + 1;
		                			s[j].addr = LC;	
		                			fprintf(fp1,"(DL, %d)\t\t%d\n",i,LC);
		                		}
					}
		                }
		        break;
		                
		}
		printf("%s\t%s\t%s\t%s\tCount - %d\n",token1,token2,token3,token4,tokencnt);
	}
	printf("\n");
	printf("Pool Table\n");
	printf("\n");
	for(i = 0;i < lenpool;i++)
	{
		
		printf("%d\t",pooltab[i]);
	}
	printf("\n");
	printf("Literal Table\n");
	printf("\n");
	for(i = 0;i < lcnt;i++)
	{
		
		printf("%c\t%d\n",l[i].lit_val,l[i].lit_addr);
		fprintf(fp3,"%d\t%d\t%c\n",i,l[i].lit_addr,l[i].lit_val);
	}
	printf("\n");
	printf("Symbol Table\n");
	printf("\n");
	for(i = 0;i < scnt;i++)
	{
		
		printf("%s\t%d\n",s[i].name,s[i].addr);
		fprintf(fp2,"%d\t%s\t%d\n",i,s[i].name,s[i].addr);
	}
	return 0;
}

