//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>

#include <chrono>
#include <functional>
#include <thread>

using namespace std::chrono_literals;

template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct perf_timer
{
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();
        return std::chrono::duration_cast<Time>(end - start);
    }
};

void f()
{
// simulate work
    std::this_thread::sleep_for(2s);
}

void g(int const a, int const b)
{
// simulate work
    std::this_thread::sleep_for(1s);
}

int main()
{
    auto t1 = perf_timer<std::chrono::microseconds>::duration(f);
    auto t2 = perf_timer<std::chrono::milliseconds>::duration(g, 1, 2);
    auto total = std::chrono::duration<double, std::nano>(t1 + t2).count();
    std::cout << total << std::endl;
    return 0;
}