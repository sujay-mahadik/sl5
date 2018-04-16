#include <stdio.h>
#include <unistd.h>
int count = 0;

int attack(int N, int board [][N], int i, int j){
	int k, l;

	for (k = 0; k < N; k++) {
		if ((board[i][k] == 1) || (board[k][j] == 1))
		{
			return 1;
		}
	}

	for (k = 0; k < N; k++) {
		for (l = 0; l < N; l++) {
			if (board[k][l] == 1)
			{
				if (((k + l) == (i + j)) || ((k - l) == (i - j))) {
					return 1;
				}

			}
		}
	}
	return 0;
}

int nq(int N, int board[][N], int i){
	int j;
	if (i == N)
	{
		count++;
		int x, y;
		for(x = 0; x < N; x++){
			for(y = 0; y < N; y++){
				if (board[x][y] == 1)
				{
					printf("Q ");
				}
				else{
					printf("* ");
				}
			}
			printf("\n");
		}
		printf("\n");
		sleep(1);
		return 0;
	}
	else{
		int j;
		for( j = 0; j < N; j++){
			if (!attack(N, board, i, j))
			{
				board[i][j] = 1;
				int safe;
				safe = nq(N, board, i+1);
				if (safe == 1)
				{
					return 1;
				}

				board[i][j] = 0;
			}
		}
		return 0;
	}
}

void main(int argc, char const *argv[])
{	
	int N, i, j;
	int board[20][20];

	printf("Enter the number of Queens: ");
	scanf("%d", &N);
	

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			board[i][j] = 0;
		}
	}

	nq(N, board, 0);
	printf("Total Solutions: %d\n", count);
}