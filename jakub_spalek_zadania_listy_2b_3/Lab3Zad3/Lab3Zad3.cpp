#include <iostream>

extern "C" _int64 case_2(_int64 x, _int64 op);

int main()
{
    std::cout << "Case 0: "  << case_2(5, 0) << std::endl;
    std::cout << "Case 1: "  << case_2(5, 1) << std::endl;
    std::cout << "Case 2: "  << case_2(5, 2) << std::endl;
    std::cout << "Default: " << case_2(5, 6) << std::endl;
}
