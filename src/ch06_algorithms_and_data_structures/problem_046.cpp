//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>

template <class T>
class circular_buffer_iterator;

template <class T>
class circular_buffer;


template <class T>
class circular_buffer_iterator
{
    using self_type = circular_buffer_iterator;
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = ptrdiff_t;
public:
    circular_buffer_iterator(circular_buffer<T> const & buf,
                             size_t const pos, bool const last) :
            buffer_(buf), index_(pos), last_(last)
    {}

    self_type & operator++ ()
    {
        if (last_)
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");
        index_ = (index_ + 1) % buffer_.data_.size();
        last_ = index_ == buffer_.next_pos();
        return *this;
    }

    self_type operator++ (int)
    {
        self_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator== (self_type const & other) const
    {
        assert(compatible(other));
        return index_ == other.index_ && last_ == other.last_;
    }

    bool operator!= (self_type const & other) const
    {
        return !(*this == other);
    }

    const_reference operator* () const
    {
        return buffer_.data_[index_];
    }

    const_reference operator-> () const
    {
        return buffer_.data_[index_];
    }

private:
    bool compatible(self_type const & other) const
    {
        return &buffer_ == &other.buffer_;
    }
    circular_buffer<T> const & buffer_;
    size_t index_;
    bool last_;
};


template <class T>
class circular_buffer
{
    using const_iterator = circular_buffer_iterator<T>;
    circular_buffer() = delete;
public:
    explicit circular_buffer(size_t const size) :data_(size)
    {}
    bool clear() noexcept { head_ = -1; size_ = 0; }
    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == data_.size(); }
    size_t capacity() const noexcept { return data_.size(); }
    size_t size() const noexcept { return size_; }

    void push(T const item)
    {
        head_ = next_pos();
        data_[head_] = item;
        if (size_ < data_.size()) size_++;
    }

    T pop()
    {
        if (empty()) throw std::runtime_error("empty buffer");
        auto pos = first_pos();
        size_--;
        return data_[pos];
    }

    const_iterator begin() const
    {
        return const_iterator(*this, first_pos(), empty());
    }

    const_iterator end() const
    {
        return const_iterator(*this, next_pos(), true);
    }

private:
    std::vector<T> data_;
    size_t head_ = -1;
    size_t size_ = 0;
    size_t next_pos() const noexcept
    { return size_ == 0 ? 0 : (head_ + 1) % data_.size(); }
    size_t first_pos() const noexcept
    { return size_ == 0 ? 0 : (head_ + data_.size() - size_ + 1) %
                              data_.size(); }
    friend class circular_buffer_iterator<T>;
};

int main()
{
    circular_buffer<int> cbuf(5); // {0, 0, 0, 0, 0} -> {}
    cbuf.push(1); // {1, 0, 0, 0, 0} -> {1}
    cbuf.push(2); // {1, 2, 0, 0, 0} -> {1, 2}
    cbuf.push(3); // {1, 2, 3, 0, 0} -> {1, 2, 3}
    auto item = cbuf.pop(); // {1, 2, 3, 0, 0} -> {2, 3}
    cbuf.push(4); // {1, 2, 3, 4, 0} -> {2, 3, 4}
    cbuf.push(5); // {1, 2, 3, 4, 5} -> {2, 3, 4, 5}
    cbuf.push(6); // {6, 2, 3, 4, 5} -> {2, 3, 4, 5, 6}
    cbuf.push(7); // {6, 7, 3, 4, 5} -> {3, 4, 5, 6, 7}
    cbuf.push(8); // {6, 7, 8, 4, 5} -> {4, 5, 6, 7, 8}
    item = cbuf.pop(); // {6, 7, 8, 4, 5} -> {5, 6, 7, 8}
    item = cbuf.pop(); // {6, 7, 8, 4, 5} -> {6, 7, 8}
    item = cbuf.pop(); // {6, 7, 8, 4, 5} -> {7, 8}
    item = cbuf.pop(); // {6, 7, 8, 4, 5} -> {8}
    item = cbuf.pop(); // {6, 7, 8, 4, 5} -> {}
    cbuf.push(9); // {6, 7, 8, 9, 5} -> {9}

    return 0;
}
