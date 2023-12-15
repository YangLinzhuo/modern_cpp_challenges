//
// Created by YangLinzhuo on 2023/12/14.
//

#include <common.h>

template <typename Traits>
class unique_handle {
    using pointer = typename Traits::pointer;
    pointer m_value;
public:
    unique_handle(unique_handle const &) = delete;

    unique_handle &operator=(unique_handle const &) = delete;

    explicit unique_handle(pointer value = Traits::invalid()) noexcept
            : m_value{value} {}

    unique_handle(unique_handle &&other) noexcept
            : m_value{other.release()} {}

    unique_handle &operator=(unique_handle &&other) noexcept {
        if (this != &other)
            reset(other.release());
        return *this;
    }

    ~unique_handle() noexcept {
        Traits::close(m_value);
    }

    explicit operator bool() const noexcept {
        return m_value != Traits::invalid();
    }

    pointer get() const noexcept { return m_value; }

    pointer release() noexcept {
        auto value = m_value;
        m_value = Traits::invalid();
        return value;
    }

    bool reset(pointer value = Traits::invalid()) noexcept {
        if (m_value != value) {
            Traits::close(m_value);
            m_value = value;
        }
        return static_cast<bool>(*this);
    }

    void swap(unique_handle<Traits> &other) noexcept {
        std::swap(m_value, other.m_value);
    }
};


template <typename Traits>
void swap(unique_handle<Traits> & left, unique_handle<Traits> & right)
noexcept
{
    left.swap(right);
}

template <typename Traits>
bool operator==(unique_handle<Traits> const & left,
                unique_handle<Traits> const & right) noexcept
{
    return left.get() == right.get();
}

template <typename Traits>
bool operator!=(unique_handle<Traits> const & left,
                unique_handle<Traits> const & right) noexcept
{
    return left.get() != right.get();
}

struct null_handle_traits
{
    using pointer = HANDLE;
    static pointer invalid() noexcept { return nullptr; }
    static void close(pointer value) noexcept
    {
        CloseHandle(value);
    }
};

struct invalid_handle_traits
{
    using pointer = HANDLE;
    static pointer invalid() noexcept { return INVALID_HANDLE_VALUE; }
    static void close(pointer value) noexcept
    {
        CloseHandle(value);
    }
};
using null_handle = unique_handle<null_handle_traits>;
using invalid_handle = unique_handle<invalid_handle_traits>;

