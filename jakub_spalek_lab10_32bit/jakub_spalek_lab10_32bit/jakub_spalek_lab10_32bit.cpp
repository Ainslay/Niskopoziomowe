#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void Task1(float a, float b, float c);
float** Task2(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB);

float** MultiplyMatrices(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB);

float** Create2DMatrix(const int& rows, const int& cols);
void Delete2DMatrix(float** matrix, const int& rows);
void Fill2DMatrixWithRandom(float** matrix, const int& rows, const int& cols);
void Print2DMatrix(float** matrix, const int& rows, const int& cols);

int main()
{
	// Delta > 0
	Task1(1, 5, 6);

	// Delta = 0
	//Task1(1, -6, 9);

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
	float** cppMultiplyResult = MultiplyMatrices(matrixA, matrixB, rowsA, rowsB, colsB);
	auto cppStop = high_resolution_clock::now();
	auto cppDuration = duration_cast<nanoseconds>(cppStop - cppStart);

	auto asmStart = high_resolution_clock::now();
	float** asmMultiplyResult = Task2(matrixA, matrixB, rowsA, rowsB, colsB);
	auto asmStop = high_resolution_clock::now();
	auto asmDuration = duration_cast<nanoseconds>(asmStop - asmStart);

	cout << "Wynik mnozenia w c++:\n";
	Print2DMatrix(cppMultiplyResult, rowsA, colsB);
	cout << "Wykonanie operacji zajelo: " << cppDuration.count() << " nanosekund" <<  endl;

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

void Task1(float a, float b, float c)
{
	// delta: b b * 4 a * c * -
	
	__asm {
		fld b					// [b]
		fld st					// [b : b]
		fmulp st(1), st			// [b^2]

		fld a					// [a : b^2]
		fld1					// [1 : a : b^2]	
		fld1					// [1 : 1 : a : b^2]
		fadd					// [2 : a : b^2]
		fld st					// [2 : 2 : a : b^2]
		fadd					// [4 : a : b^2]
		fmul					// [4a : b^2]
		fmul c					// [4ac : b^2]
		fsubp st(1), st			// [b^2-4ac] obliczona delta
		
		// Nawet jeœli delta jest 0 skacze do Greater !!!!!!! ???
		fcom 					// porównanie delty i 0 (puste s(1) jest 0)
		ja Greater				// jeœli delta > 0 skacz do greater
		je Equal				// jeœli delta = 0 skacz do equal
		jb Below				// jeœli delta < 0 skacz do below
	
	Greater:
		fsqrt					// [sqrt(delta)]
		
		fld b					// [b : sqrt(delta)]
		fchs					// [-b : sqrt(delta)]
		fld st					// [-b : -b : sqrt(delta)]
		fxch st(2)				// [sqrt(delta) : -b : -b]

		fadd st(1), st			// [sqrt(delta) : -b+sqrt(delta) : -b]
		fsubp st(2), st			// [-b+sqrt(delta) : -b-sqrt(delta)]


		fld1					// [1 : -b+sqrt(delta) : -b-sqrt(delta)]
		fld1					// [1 : 1 : -b+sqrt(delta) : -b-sqrt(delta)]
		fadd					// [2 : -b+sqrt(delta) : -b-sqrt(delta)]
		fmul a					// [2a : -b+sqrt(delta) : -b-sqrt(delta)]
		fdiv st(1), st			// [2a : -b+sqrt(delta)/2a : -b-sqrt(delta)]
		fdivp st(2), st			// [-b+sqrt(delta)/2a : -b-sqrt(delta)/2a]	
		jmp End 
	Equal:
		fld b					// [b : delta]
		fchs					// [-b : delta]
		fstp st(1)				// [-b]
		fld1					// [1 : -b]
		fld1					// [1 : 1 : -b]
		fadd					// [2 : -b]
		fmul a					// [2a : -b]
		fdivp st(1), st			// [-b/2a]

		jmp End
	Below:
		// Nie ma rzeczywistych miejsc zerowych
	End:
	}
}

float** Task2(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB)
{
	float** result = Create2DMatrix(rowsA, colsB);

	__asm {
		push edi
		push esi
		push ebx

		
		mov ecx, rowsA								// iterator i

		LoopI:
			mov edi, matrixA						// adres macierzy A
			mov ebx, result							// adres macierzy wynikowej

			mov edi, [edi + 4 * ecx - 4]			// matrixA[i]
			mov ebx, [ebx + 4 * ecx - 4]			// result[i]

			push ecx								// zabezpieczamy i
			mov ecx, colsB							// iterator j

			LoopJ:
				
				mov edx, rowsB						// iterator k
				fldz								// [s]

				LoopK:
					mov esi, matrixB				// adres macierzy B
					mov esi, [esi + 4 * edx - 4]	// matrixB[k]

					fld [edi + 4 * edx - 4]			// [matrixA[i][k] : s]
					fld [esi + 4 * ecx - 4]			// [matrixB[k][j] : matrixA[i][k] : s]
					fmulp st(1), st					// [matrixB[k][j] * matrixA[i][k] : s]
					faddp st(1), st					// [s + matrixB[k][j] * matrixA[i][k]]

					dec edx
					jnz LoopK						// dopóki k > 0 skacz do LoopK

				fstp [ebx + 4 * ecx - 4]			// zapisanie wyniku mno¿enia do result[i][j]

			Loop LoopJ								// dopóki j > 0 skacz do LoopK

			pop ecx
		Loop LoopI									// dopóki i > 0 skacz do LoopK

		pop ebx
		pop esi
		pop edi
	}

	return result;
}

float** MultiplyMatrices(float** matrixA, float** matrixB, int rowsA, int rowsB, int colsB)
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

