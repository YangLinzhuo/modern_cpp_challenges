//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>
#include <mutex>
#include <thread>

template <typename T>
class double_buffer {
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using pointer = T *;
public:
    explicit double_buffer(size_t const size) :
            read_buf(size), write_buf(size)
    {}

    size_t size() const noexcept { return read_buf.size(); }
    void write(T const * const ptr, size_t const size)
    {
        std::unique_lock<std::mutex> lock(mt);
        auto length = std::min(size, write_buf.size());
        std::copy(ptr, ptr + length, std::begin(write_buf));
        write_buf.swap(read_buf);
    }

    template <class Output>
    void read(Output it) const
    {
        std::unique_lock<std::mutex> lock(mt);
        std::copy(std::cbegin(read_buf), std::cend(read_buf), it);
    }

    pointer data() const
    {
        std::unique_lock<std::mutex> lock(mt);
        return read_buf.data();
    }

    reference operator[](size_t const pos)
    {
        std::unique_lock<std::mutex> lock(mt);
        return read_buf[pos];
    }

    const_reference operator[](size_t const pos) const
    {
        std::unique_lock<std::mutex> lock(mt);
        return read_buf[pos];
    }

    void swap(double_buffer other)
    {
        std::swap(read_buf, other.read_buf);
        std::swap(write_buf, other.write_buf);
    }
private:
    std::vector<T> read_buf;
    std::vector<T> write_buf;
    mutable std::mutex mt;
};

template <typename T>
void print_buffer(double_buffer<T> const & buf)
{
    buf.read(std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

int main()
{
    double_buffer<int> buf(10);
    std::thread t([&buf]() {
        for (int i = 1; i < 1000; i += 10)
        {
            int data[] = { i, i + 1, i + 2, i + 3, i + 4,
                           i + 5, i + 6,i + 7,i + 8,i + 9 };
            buf.write(data, 10);
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(100ms);
        }
    });
    auto start = std::chrono::system_clock::now();
    do
    {
        print_buffer(buf);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(150ms);
    } while (std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - start).count() < 12);
    t.join();

    return 0;
}

