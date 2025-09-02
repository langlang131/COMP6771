#ifndef WEEK10_SMART_CONTAINER_H
#define WEEK10_SMART_CONTAINER_H

#include <memory>
#include <stdexcept>
#include <utility>
#include <initializer_list>
#include <cstddef>
#include <iterator>
#include <algorithm>

namespace week10 {

template<typename T>
class SmartContainer {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    // Default constructor
    SmartContainer() noexcept : data_(nullptr), size_(0), capacity_(0) {}

    // Initializer list constructor
    SmartContainer(std::initializer_list<T> ilist)
        : data_(nullptr), size_(0), capacity_(0) {
        reserve(ilist.size());
        for (const auto& elem : ilist) {
            push_back(elem);
        }
    }

    // Copy constructor
    SmartContainer(const SmartContainer& other)
        : data_(nullptr), size_(0), capacity_(0) {
        reserve(other.size_);
        for (size_type i = 0; i < other.size_; ++i) {
            push_back(other.data_[i]);
        }
    }

    // Move constructor
    SmartContainer(SmartContainer&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Copy assignment
    SmartContainer& operator=(const SmartContainer& other) {
        if (this != &other) {
            SmartContainer tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // Move assignment
    SmartContainer& operator=(SmartContainer&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    reference operator[](size_type pos) { return data_[pos]; }
    const_reference operator[](size_type pos) const { return data_[pos]; }

    bool operator==(const SmartContainer& rhs) const noexcept {
        if (size_ != rhs.size_) return false;
        for (size_type i = 0; i < size_; ++i) {
            if (!(data_[i] == rhs.data_[i])) return false;
        }
        return true;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }
    void push_back(T&& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(value);
    }
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = T(std::forward<Args>(args)...);
    }
    void clear() noexcept { size_ = 0; }
    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    reference at(size_type pos) {
        if (pos >= size_) throw std::out_of_range("SmartContainer::at: out of range");
        return data_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size_) throw std::out_of_range("SmartContainer::at: out of range");
        return data_[pos];
    }

    // Iterator support
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        iterator(pointer ptr) : ptr_(ptr) {}
        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }
        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }
        iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        iterator operator+(difference_type n) const { return iterator(ptr_ + n); }
        iterator operator-(difference_type n) const { return iterator(ptr_ - n); }
        difference_type operator-(const iterator& rhs) const { return ptr_ - rhs.ptr_; }
        bool operator==(const iterator& rhs) const { return ptr_ == rhs.ptr_; }
        bool operator!=(const iterator& rhs) const { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };
    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        const_iterator(pointer ptr) : ptr_(ptr) {}
        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }
        const_iterator& operator++() { ++ptr_; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
        const_iterator& operator--() { --ptr_; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }
        const_iterator& operator+=(difference_type n) { ptr_ += n; return *this; }
        const_iterator& operator-=(difference_type n) { ptr_ -= n; return *this; }
        const_iterator operator+(difference_type n) const { return const_iterator(ptr_ + n); }
        const_iterator operator-(difference_type n) const { return const_iterator(ptr_ - n); }
        difference_type operator-(const const_iterator& rhs) const { return ptr_ - rhs.ptr_; }
        bool operator==(const const_iterator& rhs) const { return ptr_ == rhs.ptr_; }
        bool operator!=(const const_iterator& rhs) const { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };
    iterator begin() noexcept { return iterator(data_.get()); }
    iterator end() noexcept { return iterator(data_.get() + size_); }
    const_iterator begin() const noexcept { return const_iterator(data_.get()); }
    const_iterator end() const noexcept { return const_iterator(data_.get() + size_); }
    const_iterator cbegin() const noexcept { return const_iterator(data_.get()); }
    const_iterator cend() const noexcept { return const_iterator(data_.get() + size_); }

private:
    void reserve(size_type new_cap) {
        if (new_cap <= capacity_) return;
        std::unique_ptr<T[]> new_data(new T[new_cap]);
        for (size_type i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        data_ = std::move(new_data);
        capacity_ = new_cap;
    }
    std::unique_ptr<T[]> data_;
    size_type size_;
    size_type capacity_;
};

} // namespace week10

#endif 