#include <iostream>

int main()
{
    uint32_t num = 32;
    uint16_t num2 = num >> 8;
    uint16_t num3 = num2 >> 16;
    
    std::cout << num;
}
