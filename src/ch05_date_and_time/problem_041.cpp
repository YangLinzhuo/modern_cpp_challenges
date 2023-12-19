//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>
#include <chrono>

namespace ch = std::chrono;

unsigned int week_day(int const y, unsigned int const m,
                      unsigned int const d) {
    if(m < 1 || m > 12 || d < 1 || d > 31) return 0u;
    auto const dt = ch::year_month_day{ch::year{ y }, ch::month{ m }, ch::day{ d }};
    auto const tiso = ch::weekday{ dt };
    return tiso.iso_encoding();
}

int main()
{
    auto wday = week_day(2018, 5, 9);
    std::cout << wday << std::endl;
    return 0;
}
