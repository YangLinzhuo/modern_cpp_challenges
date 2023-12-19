//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>

#include <chrono>

namespace ch = std::chrono;

auto day_of_year(int const y, unsigned int const m,
                unsigned int const d)
{
    if(m < 1 || m > 12 || d < 1 || d > 31) return 0L;
    return (ch::sys_days { ch::year{ y } / ch::month{ m } / ch::day{ d } } -
            ch::sys_days { ch::year{ y } / ch::January / 0 }).count();
}

unsigned int calendar_week(int const y, unsigned int const m,
                           unsigned int const d) {
    if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

    auto const dt = ch::year_month_day{ch::year{ y }, ch::month{ m }, ch::day{ d }};
    auto const tiso = ch::weekday{ dt };
    return (unsigned int)tiso.iso_encoding();
}

int main()
{
    int y = 0;
    unsigned int m = 0, d = 0;
    std::cout << "Year:"; std::cin >> y;
    std::cout << "Month:"; std::cin >> m;
    std::cout << "Day:"; std::cin >> d;
    std::cout << "Calendar week:" << calendar_week(y, m, d) << std::endl;
    std::cout << "Day of year:" << day_of_year(y, m, d) << std::endl;

    return 0;
}
