//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>
#include <map>
#include <iomanip>

std::map<char, double> analyze_text(std::string_view text) {
    std::map<char, double> frequencies;
    for (char ch = 'a'; ch <= 'z'; ch++)
        frequencies[ch] = 0;
    for (auto ch : text) {
        if (isalpha(ch))
            frequencies[static_cast<char>(tolower(ch))]++;
    }
    auto total = std::accumulate(
            std::cbegin(frequencies), std::cend(frequencies),
            0ull,
            [](auto sum, auto const & kvp) {
                return sum + static_cast<unsigned long long>(kvp.second);
            });
    std::for_each(
            std::begin(frequencies), std::end(frequencies),
            [total](auto & kvp) {
                kvp.second = (100.0 * kvp.second) / static_cast<double>(total);
            });
    return frequencies;
}

int main()
{
    auto result = analyze_text(R"(Lorem ipsum dolor sit amet, consectetur
adipiscing elit, sed do eiusmod tempor incididunt ut labore et
dolore magna aliqua.)");
    for (auto const & kvp : result)
    {
        std::cout << kvp.first << " : "
                  << std::fixed
                  << std::setw(5) << std::setfill(' ')
                  << std::setprecision(2) << kvp.second << std::endl;
    }

    return 0;
}