#include <iostream>
using namespace std;

extern "C" _int64 if_3(_int64 a, _int64 b);

int main()
{
	_int64 a = 5;
	_int64 b = 3;
	_int64 c;

	c = if_3(a, b);
	cout << "wynik: " << c << endl;
	system("Pause");
}