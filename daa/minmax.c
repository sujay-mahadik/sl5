#include<stdio.h>
int a[20];

void minmax(int i, int j, int *min, int *max){
	int min1 = 999, max1 = -999, mid;
	if (i==j)
	{
		*min = *max = a[i];
	}
	else if(i == (j-1)){
		if (a[i]>a[j])
		{
			*max = a[i];
			*min = a[j];
		}
		else{
			*max = a[j];
			*min = a[i];
		}
	}
	else{
		mid = (i+j)/2;

		minmax(i, mid, min, max);
		minmax(mid+1, j, &min1, &max1);

		if (*max< max1)
		{
			*max = max1;
		}
		if (*min> min1)
		{
			*min = min1;
		}
	}

	
}

void main(int argc, char const *argv[])
{	
	int n, min = 999, max = -999;
	
	printf("Enter count\n");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
	printf("Enter the elements\nA[%d]: ", i+1);
	scanf("%d", &a[i]);
	}

	minmax(0, n-1, &min, &max);
	printf("Minimum number is: %d\nMaximum number is: %d", min ,max);
	
}