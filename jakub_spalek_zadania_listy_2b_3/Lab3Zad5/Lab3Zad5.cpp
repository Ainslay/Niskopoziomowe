#include <iostream>
using namespace std;

extern "C" _int64 petla_while(_int64 N);

int main()
{

    cout << "Petla while wynik = " << petla_while(2) << endl;

}