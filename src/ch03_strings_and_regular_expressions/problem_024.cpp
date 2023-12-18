//
// Created by YangLinzhuo on 2023/12/18.
//

#include <common.h>

unsigned char hexchar_to_int(char const ch)
{
    if (ch >= '0' && ch <= '9') return static_cast<unsigned char>(ch - '0');
    if (ch >= 'A' && ch <= 'F') return static_cast<unsigned char>(ch - 'A' + 10);
    if (ch >= 'a' && ch <= 'f') return static_cast<unsigned char>(ch - 'a' + 10);
    throw std::invalid_argument("Invalid hexadecimal character");
}


std::vector<unsigned char> hexstr_to_bytes_even(std::string_view str)
{
    std::vector<unsigned char> result;
    for (size_t i = 0; i < str.size(); i += 2)
    {
        result.push_back(static_cast<unsigned char>((hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i + 1])));
    }
    return result;
}

std::vector<unsigned char> hexstr_to_bytes(std::string_view str) {
    std::vector<unsigned char> result;
    if (str.size() % 2) { // length is odd
        result.push_back(hexchar_to_int(str[0]));
        auto tmp = hexstr_to_bytes_even(str.substr(1));
        std::copy(tmp.begin(), tmp.end(), std::back_inserter(result));
    } else {
        result = hexstr_to_bytes_even(str);
    }
    return result;
}


int main()
{
    std::vector<unsigned char> expected{ 0xBA, 0xAD, 0xF0, 0x0D, 0x42 };
    std::vector<unsigned char> expected_odd{ 0x0B, 0xAD };
    assert(hexstr_to_bytes("BAADF00D42") == expected);
    assert(hexstr_to_bytes("BaaDf00d42") == expected);
    auto tmp = hexstr_to_bytes("BAD");
    assert(tmp == expected_odd);
    return 0;
}
