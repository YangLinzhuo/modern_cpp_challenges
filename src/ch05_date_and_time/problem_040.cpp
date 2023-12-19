//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>

#include <chrono>

namespace ch = std::chrono;

inline long number_of_days(
            int const y1, unsigned int const m1, unsigned int const d1,
            int const y2, unsigned int const m2, unsigned int const d2) {

    return (ch::sys_days { ch::year{ y1 } / ch::month{ m1 } / ch::day{ d1 } } -
            ch::sys_days { ch::year{ y2 } / ch::month{ m2 } / ch::day{ d2 } }).count();
}

inline long number_of_days(ch::sys_days const & first,
                          ch::sys_days const & last)
{
    return (last - first).count();
}

int main()
{
    auto diff1 = number_of_days(2016, 9, 23, 2017, 5, 15);
    std::cout << diff1 << std::endl;
    using namespace std::chrono_literals;
    auto diff2 = number_of_days(2016y/ch::September/23, 15d/ch::May/2017);
    std::cout << diff2 << std::endl;
    return 0;
}