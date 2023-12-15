//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>
#include <numeric>

unsigned int gcd(unsigned int a, unsigned int b)
{
    while (b != 0) {
        unsigned int r = a % b;
        a = b;
        b = r;
    }
    return a;
}


int main() {
    unsigned int a, b;
    std::cout << "Input a and b: ";
    std::cin >> a >> b;
    std::cout << gcd(a, b) << std::endl;
    std::cout << std::gcd(a, b) << std::endl;
    return 0;
}