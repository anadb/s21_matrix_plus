#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <iostream>
#include <limits>
namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() : arr_(nullptr), size_(0), capacity_(0) {};
  vector(size_type n) : arr_(new value_type[n]), size_(n), capacity_(n) {};
  vector(std::initializer_list<value_type> const &items)
      : arr_(new value_type[items.size()]),
        size_(items.size()),
        capacity_(items.size()) {
    size_type i = 0;
    for (const auto &item : items) {
      arr_[i++] = item;
    }
  }
  vector(const vector &v) : vector(v.size_) {
    for (size_type i = 0; i < size_; i++) {
      arr_[i] = v.arr_[i];
    }
  }
  vector &operator=(const vector &v) {
    if (this != &v) {
      delete[] arr_;
      arr_ = new value_type[v.capacity_];
      size_ = v.size_;
      capacity_ = v.capacity_;
      for (size_type i = 0; i < size_; i++) {
        arr_[i] = v.arr_[i];
      }
    }
    return *this;
  }
  vector(vector &&v) noexcept {
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = v.arr_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.arr_ = nullptr;
  }
  ~vector() {
    delete[] arr_;
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
  reference at(size_type pos) { return arr_[pos]; }
  reference operator[](size_type pos) { return *(arr_ + pos); }
  const_reference front() { return arr_[0]; }
  const_reference back() { return arr_[size_ - 1]; }
  iterator data() { return arr_; }
  iterator begin() { return arr_; }
  iterator end() { return arr_ + size_ - 1; }
  bool empty() { return arr_ == nullptr; }
  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
  }
  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Size overflow");
    }
    if (size >= size_) {
      vector<value_type> tmp(size);
      for (size_type i = 0; i < size_; i++) {
        tmp.arr_[i] = arr_[i];
      }
      tmp.size_ = size_;
      *this = std::move(tmp);
    }
  }
  size_type capacity() { return capacity_; }
  void shrink_to_fit() {
    if (capacity_ > size_) {
      vector<value_type> tmp(size_);
      for (size_type i = 0; i < size_; i++) {
        tmp.arr_[i] = arr_[i];
      }
      *this = std::move(tmp);
    }
  }
  void clear() {
    delete[] arr_;
    arr_ = nullptr;
    size_ = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    size_type idx = pos - begin();
    if (size_ >= capacity_) {
      size_type new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }
    for (size_type i = size_; i > idx; --i) {
      arr_[i] = arr_[i - 1];
    }
    arr_[idx] = value;
    ++size_;
    return begin() + idx;
  }

  void erase(iterator pos) {
    size_type idx = pos - begin();
    for (size_type i = idx; i < size_ - 1; ++i) {
      arr_[i] = arr_[i + 1];
    }
    --size_;
  }

  void push_back(const_reference value) { insert(end() + 1, value); }

  void pop_back() { erase(end()); }

  void swap(vector &other) {
    vector<value_type> tmp = other;
    other = *this;
    *this = tmp;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    vector<value_type> tmp{args...};
    iterator idx = (iterator)pos;
    for (size_type i = 0; i < tmp.size(); ++i) {
      idx = insert(idx, tmp[i]) + 1;
    }
    return idx;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end() + 1, args...);
  }

 private:
  value_type *arr_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21
#endif
