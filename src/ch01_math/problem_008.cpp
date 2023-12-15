//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>

void print_narcissistics()
{
    for (int a = 1; a <= 9; a++)
    {
        for (int b = 0; b <= 9; b++)
        {
            for (int c = 0; c <= 9; c++)
            {
                auto abc = a * 100 + b * 10 + c;
                auto arm = a * a * a + b * b * b + c * c * c;
                if (abc == arm)
                {
                    std::cout << arm << std::endl;
                }
            }
        }
    }
}

// For undetermined number of digits, may use std::next_permutation to get the number to be process
int main() {
    print_narcissistics();
    return 0;
}