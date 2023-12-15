//
// Created by YangLinzhuo on 2023/12/13.
//

#include <common.h>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <cctype>

bool validate_isbn_10(std::string_view isbn)
{
    auto valid = false;
//    if (isbn.size() == 10 &&
        // Cannot use std::isdigit directly here
        // see https://stackoverflow.com/questions/75868796/differences-between-isdigit-and-stdisdigit
//        std::ranges::count_if(isbn | std::views::all, isdigit) == 10)
    if (isbn.size() == 10 &&
        std::ranges::count_if(isbn | std::views::all, [](unsigned char c){return std::isdigit(c);}) == 10)
    {
        auto w = 10;
        auto sum = std::accumulate(
                std::begin(isbn), std::end(isbn), 0,
                [&w](int const total, char const c) {
                    return total + w-- * (c - '0'); });
        valid = !(sum % 11);
    }
    return valid;
}

int main() {
//    std::string isbn = "3-16-148410-0";
    std::string isbn = "3161484100";
    std::cout << validate_isbn_10(isbn) << std::endl;
    return 0;
}