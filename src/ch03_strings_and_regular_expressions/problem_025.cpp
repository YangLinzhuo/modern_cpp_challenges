//
// Created by YangLinzhuo on 2023/12/18.
//

#include <common.h>
#include <sstream>

template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
    tstringstream<Elem> result;
    bool newWord = true;
    for (auto const ch : text) {
        newWord = newWord || std::ispunct(ch) || std::isspace(ch);
        if (std::isalpha(ch)) {
            if (newWord)
            {
                result << static_cast<Elem>(std::toupper(ch));
                newWord = false;
            }
            else { result << static_cast<Elem>(std::tolower(ch)); }
        }
        else { result << ch; }
    }
    return result.str();
}

template <class Elem>
void capitalize(tstring<Elem> & text) {
    tstringstream<Elem> result;
    auto transform_func = [new_word = true](auto& ch) mutable {
        new_word = new_word || std::ispunct(ch) || std::isspace(ch);
        if (std::isalpha(ch)) {
            if (new_word) {
                new_word = false;
                ch = static_cast<Elem>(std::toupper(ch));
            } else {
                ch = static_cast<Elem>(std::tolower(ch));
            }
        }
    };
    std::ranges::for_each(text, transform_func);
}

int main()
{
    using namespace std::string_literals;
    std::string in{"the c++ chaLLenger"};
    capitalize(in);
    assert("The C++ Challenger"s == in);
    assert("This Is An Example, Should Work!"s ==
           capitalize("THIS IS an ExamplE, should wORk!"s));
    return 0;
}