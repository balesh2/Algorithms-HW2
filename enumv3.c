#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Locker
{
	int key;
	int ball;
	int open;
};

int main()
{
	int j, mincost, t, cost, x, y;
	long i;
	//SAMPLE 1
	/*	
	int N = 3;
	int M = 1;
	int T = 1;
	int m[1];
	int k[1] = {1};
	int b[1] = {3};

	struct Locker L[3];
	int C[1][1];
	*/

	//SAMPLE 2
	/*	
	int N = 4;
	int M = 2;
	int T = 2;
	int m[4];
	int k[2] = {2, 3};
	int b[2] = {1, 4};

	struct Locker L[4];
	int C[2][2];
	*/

	//SAMPLE 3
	/*	
	int N = 8;
	int M = 2;
	int T = 2;
	int m[8];
	int k[2] = {1, 8};
	int b[2] = {5, 4};

	struct Locker L[8];
	int C[2][2];
	*/	

	//SAMPLE 4
		
	int N = 13;
	int M = 5;
	int T = 6;
	int m[5];
	int k[5] = {6, 4, 2, 7, 5};
	int b[6] = {13, 1, 6, 9, 4, 2};

	struct Locker L[13];
	int C[5][5];
	

	//SAMPLE 5
	/*	
	int N = 67;
	int M = 16;
	int T = 14;
	int m[16];
	int k[16] = {12, 53, 32, 18, 11, 48, 17, 63, 7, 54, 20, 4, 6, 8, 14, 56};
	int b[14] = {66, 32, 38, 16, 8, 40, 19, 52, 53, 12, 21, 51, 22, 18};

	struct Locker L[67];
	int C[16][16];
	*/	

	//SAMPLE 6
	/*	
	int N = 139;
	int M = 50;
	int T = 56;
	int m[50];
	int k[50] = {8, 121, 112, 9, 28, 84, 82, 129, 31, 91, 138, 25, 59, 89, 52, 36, 33, 110, 54, 37, 79, 109, 55, 16, 96, 26, 93, 101, 76, 104, 113, 139, 118, 47, 63, 128, 123, 15, 136, 132, 44, 70, 49, 86, 11, 23, 22, 39, 69, 68};
	int b[56] = {86, 33, 92, 19, 125, 41, 14, 60, 75, 135, 50, 61, 57, 28, 104, 43, 129, 128, 83, 48, 133, 65, 45, 114, 55, 11, 58, 97, 17, 42, 91, 138, 34, 127, 2, 35, 103, 49, 18, 118, 111, 74, 101, 124, 113, 47, 70, 52, 5, 139, 69, 93, 13, 29, 40, 12};
	struct Locker L[139];
	int C[50][50];
	*/	

	mincost = N;

	for(i = 0; i < M; i++)
	{
		m[i] = 0;
	}
	m[M-1] = 1;
	
	for(i = 0; i < ((long)(pow(2, M)-1)); i++)
	{	
		cost = 0;
		
		for(j = 0; j<N; j++)
		{
			L[j].open = 0;
			L[j].key = 0;
			L[j].ball = 0;
		}

		for(j = 0; j<M; j++)
		{
			if(m[j] == 1)
			{
				L[k[j]-1].key = 1;
				L[k[j]-1].open = 1;
			}
		}
				
		for(j = 0; j < T; j++)
		{
			L[b[j]-1].ball = 1;
		}
					
		j = 0;
		
		while(j < N)
		{
			if(L[j].open != 1)
			{
				if(j == N-1)
				{
					t = 0;
					while(L[j-t].open != 1)
					{
						L[j-t].open = 1;
						t++;
					}
				}
				if(L[j].key == 1)
				{
					L[j].open = 1;
				}
				if(L[j].ball == 1 && (L[j-1].open == 1 || L[j+1].open == 1))
				{
					L[j].open = 1;
				}
				if (L[j].ball == 1)
				{
					t = 0;

					while(L[j+t].open != 1 && L[j-t].open != 1)
					{
						t++;
				
						if(j+t>=N)
						{
							while(L[j-t].open != 1)
							{
								t++;
							}
							break;
						}
						if(j-t<0)
						{
							while(L[j+t].open != 1)
							{
								t++;
							}
							break;
						}
					}
					
				
					if(L[j-t].open == 1)
					{
						for(x=0; x<t; x++)
						{
							L[j-x].open = 1;
						}
					}
					else if(L[j+t].open == 1)
					{
						for(x = 0; x<t; x++)
						{
							L[j+x].open = 1;
						}
					}
				}
			}
			j++;

		}
		/*
		if(L[N-1].ball == 1)
		{
			printf("I'm in here\n");
			t = 1;
			while(L[N-1-t].open != 1)
			{
				printf("Here 1\n");
				t++;
			}
			for(x = 0; x < t+1; x++)
			{
				printf("Here 2\n");
				L[N-x].open = 1;
			}
		}
		*/
		for(x=0; x < N; x++)
		{
			if(L[x].open == 1)
			{
				cost++;
			}
		}
		
		y=M-1;
		while(m[y] == 1)
		{
			m[y] = 0;
			y--;
		}
		m[y] = 1;

		for(x = 0; x < M; x++)
		{
			printf("%d", m[x]);
		}
		printf("\n");

		if(cost < mincost)
		{
			mincost = cost;
			printf("New best\n");

			for(j = 0; j < N; j++)
			{
				printf("%d", L[j].key);
			}
			printf("\n");
			for(j = 0; j < N; j++)
			{
				printf("%d", L[j].ball);
			}
			printf("\n");
			for(j=0; j < N; j++)
			{
				printf("%d", L[j].open);
			}
			printf("\n\n\n");

		}
	}

	printf("min: %d\n", mincost);

	return 0;
}

