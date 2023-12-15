//
// Created by YangLinzhuo on 2023/12/14.
//

#include <common.h>

template <typename Type>
Type minimum(Type const a, Type const b) { return a < b ? a : b; }

template <typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
    return minimum(a, minimum(args...));
}

template <typename Comp, typename Type>
Type minimum_comp(Comp const comp, Type const a, Type const b)
{
    return comp(a, b) ? a : b;
}

template <typename Comp, typename T1, typename... T>
T1 minimum_comp(Comp const comp, T1 a, T... args)
{
    return minimum_comp(comp, a, minimum_comp(comp, args...));
}

int main()
{
    auto x = minimum(5, 4, 2, 3);
    auto y = minimum_comp(std::less<>(), 3, 2, 1, 0);
    std::cout << std::format("Minimum: {}\n", x);
    std::cout << std::format("Minimum: {}\n", y);
    return 0;
}