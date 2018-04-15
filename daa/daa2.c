#include <stdio.h>

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp; 
}

void bubblesort(int arr[], int n){
	int i,j;
	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++)
		{
			if (arr[j]>arr[j+1])
			{
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

void printarr(int arr[], int n){
	for (int i = 0; i < n; i++)
	{
		printf("[%d]:", arr[i]);
	}
}

void main(int argc, char const *argv[])
{	
	int i, j, nofiles, file[20];
	int notapes, tapesizes[20], tapes[20][20], l[20] = {0};

	printf("Enter the number of files: ");
	scanf("%d", &nofiles);
	
	for (i = 0; i < nofiles; i++)
	{
		printf("Enter the size of FILE [%d]: ", i+1);
		scanf("%d", &file[i]);
	}

	printf("\n");
	printf("Input files\n");
	printarr(file, nofiles);

	bubblesort(file, nofiles);

	printf("\n");
	printf("Sorted files according to size\n");
	printarr(file, nofiles);
	
	printf("\n\n");
	printf("Enter the number of tapes\n");
	scanf("%d", &notapes);

	for (i = 0; i < notapes; i++)
	{
		printf("Enter the size of TAPE [%d]: ", i+1);
		scanf("%d", &tapesizes[i]);
	}

	int k = 0;

	printf("\n\n");
	for (i = 0; i < nofiles; i++)
	{
		if (tapesizes[i%notapes] >= file[i])
		{
			tapesizes[i%notapes] = tapesizes[i%notapes] - file[i];	
			tapes[i%notapes][l[i%notapes]] = file[i];
			l[i%notapes]++;	
		}
		else
		{	
			for (j = 0; j < notapes; j++)
			{	
				if (tapesizes[j%notapes] >= file[i])
				{
					tapesizes[j%notapes] = tapesizes[j%notapes] - file[i];
					tapes[j%notapes][l[j%notapes]] = file[i];
					l[j%notapes]++;
					printf("Placed FILE[%d] in TAPE[%d]\n", i+1, j%notapes+1 );
				}
				else
				{
					printf("No space left for FILE[%d] in TAPE[%d]\n", i+1, j%notapes+1 );
				}
				
			}
			
		}
	}

	int sum[20] = {0};

	for (i = 0; i < notapes; i++)
	{
		printf("\nTAPE %d:\t",i+1);

		for(j = 0; j < l[i]; j++)
		{
			printf("[%d]\t", tapes[i][j]);
			sum[i] = sum[i] + tapes[i][j];
		}

		printf("\t\tRemaining size of TAPE %d: %d\n", i+1, tapesizes[i]);
	}

	for (i = 0; i < notapes; i++)
	{
		printf("\nTotal time for TAPE[%i]: %d",i+1, sum[i] );
		printf("\nMRT for TAPE[%i]: %f",i+1, sum[i]/(float)l[i] );
	}
}