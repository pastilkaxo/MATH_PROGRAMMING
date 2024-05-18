#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <Windows.h>
#include <memory.h>
#include "Levenshtein.h"
#include "MultyMatrix.h"
#include <cmath>

#define N 6
#define INFINITY  0x7fffffff
#define NINFINITY 0x80000000

#define LEN_ONE 300
#define LEN_TWO 150

using namespace std;


int Len(char* s) {
	return strlen(s);
}

char* Prefix(char* s, int k) {
	char* NewOne = new char[k];
	memcpy(NewOne, s, k);
	NewOne[k] = '\0';
	return NewOne;
}



char* RandString(int size) {

	const char symbols[] = "abcdefghijklmnopqrstuvwxyz";

	char* s = new char[size];

	for (int i = 0; i < size; i++)
	{
		s[i] = symbols[rand() % 26];
	}
	s[size] = '\0';
	return s;
}



void Task2(char *s1 , char* s2){
	setlocale(LC_ALL, "rus");

	double k[7] = {1.0/25 , 1.0/20 , 1.0/15 , 1.0/10 , 1.0/5 , 0.5 , 1.0};
	clock_t t1 = 0, t2 = 0, t3, t4;

	int lenS1 = Len(s1);
	int lenS2 = Len(s2);
	int nk1, nk2;
	char* s1_prefixed;
	char* s2_prefixed;


	std::cout << std::endl;
	std::cout << std::endl << "-- расстояние Левенштейна -----" << std::endl;
	std::cout << std::endl << "--длина --- рекурсия -- дин.програм. ---"
		<< std::endl;
	for (int i = 0; i < sizeof(k); i++)
	{
		double ki = k[i];
		nk1 = round(ki * lenS1);
		nk2 = round(ki * lenS2);
		s1_prefixed = Prefix(s1, nk1);
		s2_prefixed = Prefix(s2, nk2);
		t1 = clock();
		levenshtein_r(nk1, s1_prefixed, nk2, s2_prefixed);
		t2 = clock();
		t3 = clock();
		levenshtein(nk1, s1_prefixed, nk2, s2_prefixed);
		t4 = clock();

		cout << right << setw(3) << nk1 << "|" << setw(3) << nk2
			<< "        " << left << setw(10) << (t2 - t1)
			<< "   " << setw(10) << (t4 - t3) << endl;
	}
	system("pause");

}

void Task1() {

	char* s1 = RandString(LEN_ONE);
	cout << "S1 ("<<Len(s1)<< "): " << s1 << endl;

	char* s2 = RandString(LEN_TWO);
	cout << "S2 (" << Len(s2) << "): " << s2 << endl;

	Task2(s1, s2);

}

// расстановка скобок (рекурсия) 
int OptimalM(int i, int j, int n, const int c[], int* s)
{
#define OPTIMALM_S(x1,x2)  (s[(x1-1)*n+x2-1])  
	int o = INFINITY, bo = INFINITY;
	if (i < j)
	{
		for (int k = i; k < j; k++)
		{
			bo = OptimalM(i, k, n, c, s) +
				OptimalM(k + 1, j, n, c, s) + c[i - 1] * c[k] * c[j];
			if (bo < o)
			{
				o = bo;
				OPTIMALM_S(i, j) = k;
			}
		}
	}
	else  o = 0;
	return o;
#undef OPTIMALM_S             
};


//    расстановка скобок (динамическое программирование)  
int OptimalMD(int n, const int c[], int* s)
{
#define OPTIMALM_S(x1,x2)  (s[(x1-1)*n+x2-1]) 
#define OPTIMALM_M(x1,x2)  (M[(x1-1)*n+x2-1])
	int* M = new int[n * n], j = 0, q = 0;
	for (int i = 1; i <= n; i++) OPTIMALM_M(i, i) = 0;
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			j = i + l - 1;
			OPTIMALM_M(i, j) = INFINITY;
			for (int k = i; k <= j - 1; k++)
			{
				q = OPTIMALM_M(i, k) + OPTIMALM_M(k + 1, j) + c[i - 1] * c[k] * c[j];
				if (q < OPTIMALM_M(i, j))
				{
					OPTIMALM_M(i, j) = q;  OPTIMALM_S(i, j) = k;
				}
			}
		}
	}
	return OPTIMALM_M(1, n);
#undef OPTIMALM_M
#undef OPTIMALM_S 
};


void Task5() {
	int Mc[N + 1] = { 100,15,20,43,70,40,71}, Ms[N][N], r = 0, rd = 0;
	clock_t t1, t2, t3, t4;

	memset(Ms, 0, sizeof(int) * N * N);
	t1 = clock();
	r = OptimalM(1, N, N, Mc, OPTIMALM_PARM(Ms));
	t2 = clock();
	setlocale(LC_ALL, "rus");
	std::cout << std::endl;
	std::cout << std::endl << "-- расстановка скобок (рекурсивное решение) "
		<< std::endl;
	std::cout << std::endl << "размерности матриц: ";
	for (int i = 1; i <= N; i++) {
		std::cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
	}
	std::cout << std::endl << "минимальное количество операций умножения: " << r;
	std::cout << std::endl << std::endl << "матрица S" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < N; j++)  std::cout << Ms[i][j] << "  ";
	}
	std::cout << std::endl << endl;
	cout << "Затраченное время: " << t2 - t1 << endl;

	// ----------

	memset(Ms, 0, sizeof(int) * N * N);
	t3 = clock();
	rd = OptimalMD(N, Mc, OPTIMALM_PARM(Ms));
	t4 = clock();
	std::cout << std::endl
		<< "-- расстановка скобок (динамичеое программирование) " << std::endl;
	std::cout << std::endl << "размерности матриц: ";
	for (int i = 1; i <= N; i++) {
		std::cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
	}
	std::cout << std::endl << "минимальное количество операций умножения: "
		<< rd;
	std::cout << std::endl << std::endl << "матрица S" << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < N; j++)  std::cout << Ms[i][j] << "  ";
	}
	std::cout << std::endl << std::endl;
	cout << "Затраченное время: " << t4 - t3 << endl;
	system("pause");


}


int main()
{
	Task5();
	Task1();
	
}

