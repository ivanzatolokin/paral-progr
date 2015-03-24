// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//


#include <omp.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int size = 20;
int a[size][size];
int b[size][size];
int c[size][size];

int main()
{
	setlocale(LC_ALL, "Russian");
	int sum;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++)
			a[i][j] = rand() % 60 + 20;
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++)
			b[i][j] = rand() % 60 + 20;
	}

	//cout << "Матрица А" << endl;
	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		cout << a[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	//cout << "Матрица B" << endl;
	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		cout << b[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	double begin = omp_get_wtime();

#pragma omp parallel for private (sum)
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			sum = 0;
			for (int j = 0; j < size; j++) {
				sum += a[i][j] * b[j][k];
			}
			c[i][k] = sum;
		}
	}
	cout << "Время работы параллельного выполнения - " << (omp_get_wtime() - begin) << endl;

	begin = omp_get_wtime();

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			sum = 0;
			for (int j = 0; j < size; j++) {
				sum += a[i][j] * b[j][k];
			}
			c[i][k] = sum;
		}
	}
	cout << "Время работы последовательного выполнения - " << (omp_get_wtime() - begin) << endl;

	//cout << "Матрица C" << endl;
	//for (int i = 0; i < size; i++) {
	//	for (int j = 0; j < size; j++) {
	//		cout << c[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cin.ignore();
}


