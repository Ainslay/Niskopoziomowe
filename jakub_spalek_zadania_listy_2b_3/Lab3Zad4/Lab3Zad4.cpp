#include <iostream>

extern "C" _int64 silnia_for_jnz(_int64 n);
extern "C" _int64 silnia_for_loop(_int64 n);

int main()
{
    std::cout << "JNZ 5! = " << silnia_for_jnz(5) << std::endl;
    std::cout << "LOOP 5! = " << silnia_for_loop(5) << std::endl;
}