#include <stdio.h>
int distMat[10][10], completed[10], n, cost = 0;

void getData(){
	printf("Enter the number of cities: ");
	scanf("%d", &n);

	printf("Enter the Cost Matrix\n");

	int i, j;

	for(i = 0; i < n; i++){
		printf("Enter the row %d elements\n", i+1 );
		for(j = 0; j < n; j++){
			scanf("%d", &distMat[i][j]);
		}
		completed[i] = 0;
	}
}

int least (int c){
	int i, nc = 999;
	int min = 999, kmin;

	for(i = 0; i < n; i++){
		if ((distMat[c][i] != 0) && (completed[i] == 0))
		{
			if (distMat[c][i] + distMat[i][c] < min)
			{
				min = distMat[c][i] + distMat [i][c];
				kmin = distMat[c][i];
				nc = i;
			}
		}
	}

	if (min != 999)
	{
		cost += kmin;
	}
	return nc;
}

void mincost(int city){
	int i, ncity;
	completed[city] = 1;

	printf("%d --> ", city + 1 );
	ncity = least(city);

	if (ncity == 999)
	{
		ncity = 0;
		printf("%d", ncity+1 );
		cost += distMat[city][ncity];
		return;
	}

	mincost(ncity);
}

int main(int argc, char const *argv[])
{
	getData();
	mincost(0);
	printf("Minimum cost is %d\n", cost );
	return 0;
}