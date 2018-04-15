#include <stdio.h>

int N, board[20][20];

int attack(int i, int j) {
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

int nq(int n) {
	int i, j;

	if (n == 0)
	{
		return 1;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (( !attack(i, j) ) && ( board[i][j] != 1 ))
			{
				board[i][j] = 1;

				if (nq(n - 1) == 1)
				{
					return 1;
				}

				board[i][j] = 0;
			}
		}
	}
	return 0;
}
void main(int argc, char const *argv[])
{
	printf("Enter the number of Queens\n");
	scanf("%d", &N);



	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}

	nq(N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (board[i][j] == 1)
			{
				printf(" Q");
			}
			else {
				printf(" *");
			}

		}
		printf("\n");
	}
}