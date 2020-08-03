#include <iostream>
#include <time.h>

using namespace std ;

void print_elapsed(clock_t start, clock_t stop)
{
	double elapsed = ((double)(stop - start)) / CLOCKS_PER_SEC ; // elapsed ; 시작 ~ 끝, 경과 시간
	cout << "Elapsed time : " << elapsed << "sec" << endl ; // 경과 시간을 출력 (sec)
}

void showall(int **Icol, int a, int b, int *weight) // item 목록 출력
{
	if( a <= 0 || b <= 0 )
	{
		return ;
	}

	if( Icol[a][b] == a )
	{
		cout << "item " << a << " " ;
		showall(Icol, a-1, b-weight[a], weight) ;
	}else
	{
		showall(Icol, a-1, b, weight) ;
	}
}

int knapsack(int *price, int *weight, int n, int w) // 0-1 DP knapsack
{
	int **MaxP = new int*[n+1] ;
	int **Icol = new int*[n+1] ;
	
	for( int i = 0 ; i <= n ; i++ )
	{
		MaxP[i] = new int[w+1] ;
		Icol[i] = new int[w+1] ;
	}

	for( int i = 0 ; i <= n ; i++ ) // 아이템 목록 초기화
	{
		for( int v = 0 ; v <= w ; v++ )
		{
			Icol[i][v] = 0 ;
		}
	}
	
	for( int i = 0 ; i <= n ; i++ )
	{
		for( int v = 0 ; v <= w ; v++ )
		{
			if( i == 0 || v == 0 )
			{
				MaxP[i][v] = 0 ;
			}else if( weight[i] <= v )
			{
				if( price[i] + MaxP[i-1][v-weight[i]] > MaxP[i-1][v] ) // 아이템을 포함하는것이 Price가 높다면
				{
					MaxP[i][v] = price[i] + MaxP[i-1][v-weight[i]] ; // i번째를 포함하여 계산 후
					Icol[i][v] = i ; // i번째 포함하였다고 표시
				}else
				{
					MaxP[i][v] = MaxP[i-1][v] ; // 아니면 포함하지 않음
				}
			}else if( weight[i] > v )
			{
				MaxP[i][v] = MaxP[i-1][v] ;
			}
		}
	}

	for( int i = 1 ; i <= n ; i++ )
	{
		for( int v = 1 ; v <= w ; v++ )
		{
			if( Icol[i][v] == 0 && Icol[i-1][v] != 0 )
			{
				Icol[i][v] = Icol[i-1][v] ;
			}
		}
	}

	cout << "What items in it ?" << endl ;

	showall(Icol, n, w, weight) ;

	cout << endl ;

	return MaxP[n][w] ;
}

int main()
{
	cout << "12141680 김지훈 DP Project" << endl << endl ;

	clock_t start, stop ;

	int n, w ;
	
	cout << "How many items : " ;
	cin >> n ;

	int *Price = new int[n+1] ;
	int *Weight = new int[n+1] ;

	cout << endl << "Enter Price & Weight of item" << endl ;

	for( int i = 1 ; i <= n ; i++ )
	{
		cout << "item " << i << " : " ;
		cin >> Price[i] >> Weight[i] ;
	}

	cout << endl << "Enter the Capacity of Knapsack : " ;
	cin >> w ;

	cout << endl ;
	start = clock() ; // Dynamic Programming 시작
	cout << endl << "Maximum Price : " << knapsack(Price, Weight, n, w) ;
	stop = clock() ; // Dynamic Programming 종료
	cout << endl << endl ;
	
	print_elapsed(start, stop) ; // 경과 시간 출력

	return 0 ;
}