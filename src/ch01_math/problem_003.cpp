//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>
#include <numeric>

int lcm(int const a, int const b)
{
    int h = std::gcd(a, b);
    return h ? (a * (b / h)) : 0;
}

// compute the lcm for more than two integers
template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
    return std::accumulate(first, last, 1, lcm);
}

int main() {
    int a, b;
    std::cout << "Input a and b: ";
    std::cin >> a >> b;
    std::cout << lcm(a, b) << std::endl;
    std::cout << std::lcm(a, b) << std::endl;
    return 0;
}