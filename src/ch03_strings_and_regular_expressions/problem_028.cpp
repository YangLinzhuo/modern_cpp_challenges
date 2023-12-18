//
// Created by YangLinzhuo on 2023/12/18.
//

#include <common.h>

std::string longest_palindrome(std::string_view str) {
    size_t const len = str.size();
    size_t longest_begin = 0;
    size_t max_len = 1;
    auto offset = [len](size_t i, size_t j){
        return i * len + j;
    };
    std::vector<bool> table(len * len, false);
    for (size_t i = 0; i < len; i++)
        table[offset(i, i)] = true;
    for (size_t i = 0; i + 1 < len; i++)
    {
        if (str[i] == str[i + 1])
        {
            table[offset(i, i + 1)] = true;
            if (max_len < 2)
            {
                longest_begin = i;
                max_len = 2;
            }
        }
    }

    for (size_t k = 3; k <= len; k++) {
        for (size_t i = 0; i + (k - 1) < len; i++) {
            size_t j = i + k - 1;
            if (str[i] == str[j] && table[offset(i + 1, j - 1)]) {
                table[offset(i, j)] = true;
                if (max_len < k)
                {
                    longest_begin = i;
                    max_len = k;
                }
            }
        }
    }
    return std::string(str.substr(longest_begin, max_len));
}

int main() {
    using namespace std::string_literals;
    assert(longest_palindrome("sahararahnide") == "hararah");
    assert(longest_palindrome("level") == "level");
    assert(longest_palindrome("s") == "s");
    return 0;
}