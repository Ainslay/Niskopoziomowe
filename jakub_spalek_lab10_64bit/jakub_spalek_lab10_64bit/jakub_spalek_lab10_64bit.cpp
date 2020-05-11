// Opracowane przez: Jakub Spa³ek, Aleksandra Pyrkosz, Daniel Wiêcek
// Wersja 64 NIE DZIA£A, nie byliœmy w stanie jej rozwi¹zaæ 





#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void Task1();
void Task2();

extern "C" float** AsmMultiplyMatrices64(float** matrixA, float** matrixB, float** result, int rowsA, int rowsB, int colsB);
extern "C" float QuadraticEquation64(float a, float b, float c, float* roots);
float** CppMultiplyMatrices(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB);

void QuadraticEquation(float a, float b, float c);
float** Create2DMatrix(const int& rows, const int& cols);
void Delete2DMatrix(float** matrix, const int& rows);
void Fill2DMatrixWithRandom(float** matrix, const int& rows, const int& cols);
void Print2DMatrix(float** matrix, const int& rows, const int& cols);

int main()
{
	Task1();
	//Task2();
}

void Task1()
{
	// Delta > 0
	QuadraticEquation(1, 5, 6);

	// Delta = 0
	QuadraticEquation(1, -6, 9);

	// Delta < 0
	QuadraticEquation(1, 2, 9);

	cout << endl;
	system("pause");
	system("cls");
}

void Task2()
{
	int rowsA, colsA;
	int rowsB, colsB;

	cout << "Podaj liczbe wierszy macierzy A: "; cin >> rowsA;
	cout << "Podaj liczbe kolumn macierzy A: "; cin >> colsA;
	cout << "Podaj liczbe wierszy macierzy B: "; cin >> rowsB;
	cout << "Podaj liczbe kolumn macierzy B: "; cin >> colsB;
	system("cls");

	if (colsA != rowsB)
	{
		cerr << "\nLiczba kolumn macierzy A i wierszy macierzy B musi byæ taka sama!";
		exit(-1);
	}

	float** matrixA = Create2DMatrix(rowsA, colsA);
	float** matrixB = Create2DMatrix(rowsB, colsB);

	Fill2DMatrixWithRandom(matrixA, rowsA, colsA);
	Fill2DMatrixWithRandom(matrixB, rowsB, colsB);

	cout << "Macierz A:\n";
	Print2DMatrix(matrixA, rowsA, colsA);

	cout << "Macierz B:\n";
	Print2DMatrix(matrixB, rowsB, colsB);

	auto cppStart = high_resolution_clock::now();
	float** cppMultiplyResult = CppMultiplyMatrices(matrixA, matrixB, rowsA, rowsB, colsB);
	auto cppStop = high_resolution_clock::now();
	auto cppDuration = duration_cast<nanoseconds>(cppStop - cppStart);

	float** asmMultiplyResult = Create2DMatrix(rowsA, colsB);
	auto asmStart = high_resolution_clock::now();
	AsmMultiplyMatrices64(matrixA, matrixB, asmMultiplyResult, rowsA, rowsB, colsB);
	auto asmStop = high_resolution_clock::now();
	auto asmDuration = duration_cast<nanoseconds>(asmStop - asmStart);

	cout << "Wynik mnozenia w c++:\n";
	Print2DMatrix(cppMultiplyResult, rowsA, colsB);
	cout << "Wykonanie operacji zajelo: " << cppDuration.count() << " nanosekund" << endl;

	cout << "\nWynik mnozenia w assemblerze:\n";
	Print2DMatrix(asmMultiplyResult, rowsA, colsB);
	cout << "Wykonanie operacji zajelo: " << asmDuration.count() << " nanosekund" << endl;

	cout << "\nStosunek czasu wykonania cpp do asm: " << cppDuration.count() / asmDuration.count() << endl;

	Delete2DMatrix(cppMultiplyResult, rowsA);
	Delete2DMatrix(asmMultiplyResult, rowsA);
	Delete2DMatrix(matrixA, rowsA);
	Delete2DMatrix(matrixB, rowsB);

	cout << endl;
	system("pause");
}

void QuadraticEquation(float a, float b, float c)
{
	// delta: b b * 4 a * c * -
	float* roots = new float[2]{ 0, 0 };
	float delta = QuadraticEquation64(a,b,c,roots);

	if (delta > 0)
	{
		cout << "Miejsca zerowe: x1 = " << roots[0] << " " << "x2 = " << roots[1] << endl;
	}
	else if (delta == 0)
	{
		cout << "Miejsce zerower: x1 = " << roots[0] << endl;
	}
	else
	{
		cout << "Brak miejsc zerowych w zbiorze liczb rzeczywistych" << endl;
	}
}

float** CppMultiplyMatrices(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB)
{
	float** result = Create2DMatrix(rowsA, colsB);

	for (int i = 0; i < rowsA; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			for (int k = 0; k < rowsB; k++)
			{
				result[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	return result;
}

void Fill2DMatrixWithRandom(float** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = (float)rand() / (float)(RAND_MAX / 5);
		}
	}
}

void Print2DMatrix(float** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		cout << "[";
		for (int j = 0; j < cols; j++)
		{
			if (j == cols - 1)
			{
				printf("%f", matrix[i][j]);
			}
			else
			{
				printf("%f, ", matrix[i][j]);
			}
		}
		cout << "]\n";
	}
}

float** Create2DMatrix(const int& rows, const int& cols)
{
	float** matrix = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new float[cols];

		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = 0.0f;
		}
	}

	return matrix;
}

void Delete2DMatrix(float** matrix, const int& rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

