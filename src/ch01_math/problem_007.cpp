//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>
#include <cmath>

int sum_proper_divisors(int const number)
{
    int result = 1;
    for (int i = 2; i <= std::sqrt(number); i++)
    {
        if (number % i == 0)
        {
            result += (i == (number / i)) ? i : (i + number / i);
        }
    }
    return result;
}

void print_amicables(int const limit)
{
    for (int number = 4; number < limit; ++number)
    {
        auto sum1 = sum_proper_divisors(number);
        if (sum1 < limit && number < sum1)
        {
            auto sum2 = sum_proper_divisors(sum1);
            if (sum2 == number)
            {
                std::cout << std::format("({}, {})", number, sum1) << std::endl;
            }
        }
    }
}

int main() {
    int limit = 1'000'000;
    print_amicables(limit);

    return 0;
}