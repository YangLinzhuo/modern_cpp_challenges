//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>

bool is_prime(int const num)
{
    if (num <= 3) { return num > 1; }
    else if (num % 2 == 0 || num % 3 == 0)
    {
        return false;
    }
    else
    {
        for (int i = 5; i * i <= num; i += 6)
        {
            if (num % i == 0 || num % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }
}

int main()
{
    int limit = 0;
    std::cout << "Upper limit:";
    std::cin >> limit;
    for (int i = limit; i > 1; i--)
    {
        if (is_prime(i))
        {
            std::cout << std::format("Largest prime: {}", i) << std::endl;
            break;
        }
    }
    return 0;
}