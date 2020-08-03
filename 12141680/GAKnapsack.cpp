#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std ;

#define CR 0.85    // Crossover Rate
#define MR 0.015  // Mutation Rate
#define POP_SZ 100 // POP_Size
#define NC 2       // # of Crossover point
#define NR 100     // 총 라운드 수(number of round)

void print_elapsed(clock_t start, clock_t stop)
{
	double elapsed = ((double)(stop - start)) / CLOCKS_PER_SEC ; // elapsed ; 시작 ~ 끝, 경과 시간
	cout << "Elapsed time : " << elapsed << "sec" << endl ; // 경과 시간을 출력 (sec)
}

class item // 아이템의 무게 및 가격
{
private :
	int num ;
	int weight ;
	int price ;

public :
	int getNum() ;
	int getWeight() ;
	int getPrice() ;
	void setNum(int newNum) ;
	void setWeight(int newWeight) ;
	void setPrice(int newPrice) ;
} ;

// Encoding, Binary Encoding 방식, GA 실행하기 전에 해를 랜덤하게 생성, 해를 false(0) 아니면 true(1)로 표현
int encoding(item *&itarr, bool *&sol, int totalNum, int capacity)
{
	int i = 0 ;
	int cap = 0 ;
	int pri = 0 ;

	for(;;)
	{
		cap = 0 ;
		pri = 0 ;
		for( i = 1 ; i <= totalNum ; i++ )
		{
			int a = rand() % 2 ; // 해를 랜덤하게 생성
			
			if( a == 1 )
			{
				sol[i] = true ;
			}else
			{
				sol[i] = false ;
			}

			if( sol[i] )
			{
				cap += itarr[i].getWeight() ;
				pri += itarr[i].getPrice() ;

				if( cap > capacity )
				{
					i-- ;
					break ;
				}
			}
		}
		if( i >= totalNum )	break ;
	}

	return pri ;
}

// 해를 비교하여 아이템 무게가 초과되면(부적합) 0을 반환, 그렇지 않다면 계산값을 반환
int testSol(item *&itarr, bool *&sol, int totalNum, int capacity)
{
	int i = 0 ;
	int pri = 0 ;
	int cap = 0 ;
	for( i = 1 ; i <= totalNum ; i++ )
	{
		if( sol[i] )
		{
			cap += itarr[i].getWeight() ;
			pri += itarr[i].getPrice() ;
			if( cap > capacity ) return 0 ;
		}
	}

	return pri ;
}

// Crossover, Multi-Point Crossover 방식, NC가 Point 개수 지정
int crossX(item *&itarr, bool *&sol1, bool *&sol2, bool *&newSol1, bool *&newSol2, int newSolVal1, int newSolVal2, int totalNum, int capacity)
{
	int *cut = new int[NC + 1] ;
	int i = 0, j = 0, k = 0 ;
	int cap1 = 0, cap2 = 0 ;
	int pri1 = 0, pri2 = 0 ;

	for( i = 0 ; i <= NC ; i++ )
	{
		cut[i] = rand() % totalNum + 1 ;

		for( j = 0 ; j < i; j++ )
		{
			if( cut[i] == cut[j] )
			{
				i-- ;
				break ;
			}
		}
	}

	for( i = 1 ; i <= totalNum ; i++ )
	{
		if( k % 2 )
		{
			newSol1[i] = sol2[i] ;
			newSol2[i] = sol1[i] ;
		}else
		{
			newSol1[i] = sol1[i] ;
			newSol2[i] = sol2[i] ;
		}

		if( cut[k] == i ) k++ ;

		pri1 += newSol1[i] * itarr[i].getPrice() ;
		pri2 += newSol2[i] * itarr[i].getPrice() ;
		cap1 += newSol1[i] * itarr[i].getWeight() ;
		cap2 += newSol2[i] * itarr[i].getWeight() ;

		if( cap1 > capacity || cap2 > capacity ) return 0 ;
	}

	newSolVal1 = pri1 ;
	newSolVal2 = pri2 ;

	return 1 ;
}

/*
// Selection, Roulette Selection 방식, Elitism
int selection(int *&solVal, int sumPrice)
{
	int i = 0, j = 1 ;

	double ranNum = 0 ;

	double prob = 0 ;

	while(j)
	{
		ranNum = (double)((double)(rand() % 100) / 100) ;
		for( i = 1 ; i <= POP_SZ ; i++ )
		{
			prob = (double)((double)solVal[i] / (double)sumPrice) ;
			ranNum -= prob ;
			if( ranNum <= 0 )
			{
				j = 0 ;
				break ;
			}
		}
	}
	return i ;
}
*/

// Selection, Tournament Selection 방식, Not Elitism
int selection(int totalNum, int *solVal)
{
	double maxPrice = -1 ;

	int r = 0 ;
	int ranNum = 0 ;
	int ranVal ;

	ranNum = ((rand() % 100) / totalNum) ;
	
	for( int i = 0 ; i < ranNum ; i++ )
	{
		ranVal = ((rand() % 100 / totalNum)) ;

		if( solVal[ranVal] > maxPrice )
		{
			maxPrice = solVal[ranVal] ;
			r = ranVal ;
		}
	}

	return r ;
}

// Mutaion, IM 방식
void mutation(bool *&sol, int num) // IM
{
	sol[num] = ~sol[num] ;
}

/*
// Mutation, IVM 방식
void mutation(bool *&sol, int num1, int num2) // IVM
{
	int j = num2 ;
	int a = 0 ;

	bool *temp = new bool[num2-num1+1] ;

	for( int i = num1 ; i <= num2 ; i++ )
	{
		temp[a] = sol[i] ;
		a++ ;
	}

	for( int i = num1 ; i <= num2 ; i++ )
	{
		a-- ;
		sol[i] = temp[a] ;
	}
}
*/

// 해를 이진수로 바꾼 것을 해독 -> 1이라면 아이템이 있고, 0이라면 아이템이 없음
void showSol(bool *&sol, int totalNum)
{
	for( int i = 1 ; i <= totalNum ; i++ )
	{
		if( sol[i] == 1 )
		{
			cout << "item " << i << " : O" << endl ;
		}else
		{
			cout << "item " << i << " : X" << endl ;
		}
	}
	cout << endl ;
}

// sol2 해의 값을 sol1으로 복사해주는 함수, size는 해의 길이
void copySol(bool *&sol1, bool *&sol2, int size)
{
	for( int i = 1 ; i <= size ; i++ )
	{
		sol1[i] = sol2[i] ;
	}
}

// 정답 도출을 평균적으로 무엇으로 나오는지 계산
double getAver(int *&solVal, int totalNum)
{
	int sum = 0 ;
	double aver = 0 ;
	
	for( int i = 1 ; i <= POP_SZ ; i++ )
	{
		sum += solVal[i] ;
	}

	aver = (double)sum / POP_SZ ;

	return aver ;
}

// item class의 get, set 함수 정의
int item::getNum()
{
	return num ;
}

int item::getPrice()
{
	return price ;
}

int item::getWeight()
{
	return weight ;
}

void item::setNum(int newNum)
{
	num = newNum ;
}

void item::setPrice(int newPrice)
{
	price = newPrice ;
}

void item::setWeight(int newWeight)
{
	weight = newWeight ;
}


int main(void)
{
	cout << "12141680 김지훈 GA Project" << endl << endl ;
	
	clock_t start, stop ;

	int totalNum = 0 ;
	int capacity = 0 ;

	cout << "How many items : " ;
	cin >> totalNum ;

	item *itarr = new item[totalNum + 1] ; // 아이템 배열 생성

	int price = 0 ;
	int weight = 0 ;

	cout << endl << "Enter Price & Weight of item" << endl ;

	for( int i = 1 ; i <= totalNum ; i++ )
	{
		cout << "item " << i << " : " ;
		cin >> price ;
		itarr[i].setPrice(price) ;
		cin >> weight ;
		itarr[i].setWeight(weight) ;
	}

	cout << endl << "Enter the Capacity of Knapsack : " ;
	cin >> capacity ;

	int sumPrice = 0 ;
	int i, j, k ;
	int maxPrice = -1 ; // MaxPrice를 저장
	int avrg = 0 ; // 무엇으로 평균이 도출되는지

	srand(unsigned(time(NULL))) ;

	bool **slarr = new bool*[POP_SZ + 1] ; // Original 해 배열
	bool **smarr = new bool*[POP_SZ + 1] ; // Mutation 해 배열

	for( i = 0 ; i <= POP_SZ ; i++ )
	{
		slarr[i] = new bool[totalNum + 1] ;
		smarr[i] = new bool[totalNum + 1] ;
	}

	int *slval = new int[POP_SZ + 1] ; // Original 해 배열 적합도
	int *smval = new int[POP_SZ + 1] ; // Mutation 해 배열 적합도
	bool *bestSol = new bool[totalNum + 1] ; // Best 해 배열 적합도

	start = clock() ; // GA 시작

	for( i = 1 ; i <= POP_SZ ; i++ )
	{
		slval[i] = encoding(itarr, slarr[i], totalNum, capacity) ; // Encoding
		sumPrice += slval[i] ;
	}

	// NR만큼 ROUND 반복
	for( int round = 1 ; round <= NR ; round++ )
	{
		for( i = 1 ; i < POP_SZ ; i += 2 )
		{
			j = selection(totalNum, slval) ; // Selection
			k = selection(totalNum, slval) ; // Selection

			if( rand() % 100 <= CR * 100 )
			{
				k = crossX(itarr, slarr[j], slarr[k], smarr[i], smarr[i+1], smval[i], smval[i+1], totalNum, capacity) ; // Crossover
			}else
			{
				i -= 2 ;
				continue ;
			}

			if( j == 0 || k == 0 ) i -= 2 ;
		}

		for( i = 1 ; i <= POP_SZ ; i++ )
		{
			bool *newSolMade = new bool[totalNum] ;

			copySol(newSolMade, smarr[i], totalNum) ;
			
			if( rand() % 100 <= (double)MR * 100 )
			{
				int j = rand() % totalNum ;
				int j2 = j + 1 ;

				while( j2 > totalNum )
				{
					int j = rand() % totalNum ;
					j2 = j + 1 ;
				}

				mutation(newSolMade, j) ; // Mutation
			}

			smval[i] = testSol(itarr, newSolMade, totalNum, capacity) ;

			if( smval[i] == 0 )
			{
				i-- ;
				continue ;
			}else smarr[i] = newSolMade ;
		}

		sumPrice = 0 ;

		for( i = 1 ; i <= POP_SZ ; i++ )
		{
			copySol(slarr[i], smarr[i], totalNum) ;
			slval[i] = smval[i] ;
			sumPrice += slval[i] ;

			if( slval[i] > maxPrice )
			{
				maxPrice = slval[i] ;
				copySol(bestSol, slarr[i], totalNum) ;
			}
		}

		avrg = getAver(slval, totalNum) ;

		cout << round << "th generation's average price : " << avrg << endl ;
	}

	cout << endl ;

	cout << "Maximum Price : " << maxPrice << endl << endl ;

	cout << "What items in it ?" << endl ;
	
	showSol(bestSol, totalNum) ; // Item 출력

	stop = clock() ; // GA 종료
	
	print_elapsed(start, stop) ; // 경과 시간 출력

	delete[] slval ;
	delete[] smval ;
	delete[] bestSol ;

	return 0 ;
}