//
// Created by YangLinzhuo on 2023/12/14.
//

#include <common.h>

template<typename Type, size_t Row, size_t Col>
class array2d {
private:
    using value_type = Type;
    using iterator = value_type*;
    using const_iterator = value_type const*;
    std::vector<Type> arr;
public:
    array2d(): arr(Row * Col, 0) {}
    array2d(std::initializer_list<Type> list): arr(list) {}

    constexpr Type* data() noexcept
    {
        return arr.data();
    }

    [[nodiscard]] constexpr Type const * data() const noexcept
    {
        return arr.data();
    }

    constexpr Type& at(size_t const row, size_t const col)
    {
        return arr.at(row * Col + col);
    }

    [[nodiscard]] constexpr Type const & at(size_t const row, size_t const col) const
    {
        return arr.at(row * Col + col);
    }

    constexpr Type& operator()(size_t const row, size_t const col)
    {
        return arr[row * Col + col];
    }

    [[nodiscard]] constexpr Type const & operator()(size_t const row, size_t const col) const
    {
        return arr.at(row * Col + col);
    }

    [[nodiscard]] constexpr bool empty() const noexcept { return Row == 0 || Col == 0; }

    [[nodiscard]] constexpr size_t size(int const rank) const
    {
        if (rank == 1) {
            return Row;
        } else if (rank == 2) {
            return Col;
        }
        throw std::out_of_range("Rank is out of range!");
    }

    void fill(Type const & value)
    {
        std::ranges::fill(arr, value);
    }

    void swap(array2d & other) noexcept { arr.swap(other.arr); }

    [[nodiscard]] const_iterator begin() const { return arr.data(); }
    [[nodiscard]] const_iterator end() const { return arr.data() + arr.size(); }
    iterator begin() { return arr.data(); }
    iterator end() { return arr.data() + arr.size(); }
};


int main()
{
    // element access
    array2d<int, 2, 3> a {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < a.size(1); ++i)
        for (size_t j = 0; j < a.size(2); ++j)
            a(i, j) *= 2;
    // iterating
    std::copy(std::begin(a), std::end(a),
              std::ostream_iterator<int>(std::cout, " "));
    // filling
    array2d<int, 2, 3> b;
    b.fill(1);

    // swapping
    a.swap(b);
    // moving
    array2d<int, 2, 3> c(std::move(b));
}