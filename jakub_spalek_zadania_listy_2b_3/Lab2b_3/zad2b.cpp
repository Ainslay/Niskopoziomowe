#include <iostream>
using namespace std;

extern "C" void hello_world_asm();

int main(int argc, char* argv[])
{
	hello_world_asm();
	return 0;
}