//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>

int main() {
    unsigned int limit = 0;
    std::cout << "Upper limit:";
    std::cin >> limit;
    unsigned long long sum = 0;
    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
            sum += i;
    }
    std::cout << std::format("sum = {}", sum) << std::endl;
}