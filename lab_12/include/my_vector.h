#pragma once

#include <cstddef>
#include <iosfwd>

namespace my_vector {

template <typename T>
class my_vector final {
public:
    explicit my_vector() noexcept;
    explicit my_vector(size_t);
    my_vector(const my_vector&);
    my_vector(my_vector&&) noexcept;
    my_vector& operator=(const my_vector&);
    my_vector& operator=(my_vector&&) noexcept;
    ~my_vector();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    void reserve(size_t);
    void resize(size_t);
    void resize(size_t, const T&);
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    void clear() noexcept;

    T& operator[](size_t);
    const T& operator[](size_t) const;

private:
    size_t size_;
    size_t capacity_;
    T* array_;

    void make_empty() noexcept;
    static my_vector allocate_vector(size_t, size_t);
};

template <typename T>
std::ostream& operator<<(std::ostream&, const my_vector<T>&);

} //namespace my_vector