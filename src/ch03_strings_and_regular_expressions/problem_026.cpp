//
// Created by YangLinzhuo on 2023/12/18.
//

#include <common.h>
#include <sstream>
#include <list>
#include <set>

std::string join(std::vector<std::string>& str_list, char const delimiter = ' ')
{
    if (str_list.empty()) {
        return "";
    }
    std::ostringstream out;
//    for (auto& str : str_list) {
//        out << str << delimiter;
//    }
    for (size_t i = 0; i < str_list.size(); ++i) {
        if (i + 1 == str_list.size()) {
            out << str_list[i];
        } else {
            out << str_list[i] << delimiter;
        }
    }
    return out.str();
}

template <typename Iter>
std::string join_strings(Iter begin, Iter end,
                         char const * const separator)
{
    std::ostringstream os;
    os << *begin;
    ++begin;
    for (; begin != end; ++begin) {
        os << separator << *begin;
    }
    return os.str();
}

// https://codereview.stackexchange.com/questions/207035/elegantly-exclude-part-of-an-operation-for-the-last-iteration-in-a-loop
template <typename C>
std::string join_strings(C const & c, char const * const separator)
{
    if (c.size() == 0) return std::string{};
    return join_strings(std::begin(c), std::end(c), separator);
}


int main()
{
    using namespace std::string_literals;
    std::vector<std::string> v1{ "this","is","an","example" };
    std::vector<std::string> v2{ "example" };
    std::vector<std::string> v3{ };
    std::list<std::string> l1 { "this","is","an","example" };
    std::set<std::string> s1 { "this","is","an","example" };
    assert(join_strings(v1, " ") == "this is an example"s);
    assert(join_strings(v2, " ") == "example"s);
    assert(join_strings(v3, " ") == ""s);
    assert(join_strings(l1, " ") == "this is an example"s);
    assert(join_strings(s1, " ") == "this is an example"s);
    return 0;
}
