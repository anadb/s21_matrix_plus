#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() : data_() {}
  stack(std::initializer_list<value_type> const &items) : data_(items) {}
  stack(const stack &other) : data_(other.data_) {}
  stack(stack &&other) noexcept : data_(std::move(other.data_)) {}

  stack &operator=(const stack &other) {
    data_ = other.data_;
    return *this;
  }
  stack &operator=(stack &&other) noexcept {
    data_ = std::move(other.data_);
    return *this;
  }

  reference top() { return data_.back(); }
  const_reference top() const { return data_.back(); }

  bool empty() const { return data_.empty(); }
  size_type size() const { return data_.size(); }

  void push(const_reference value) { data_.push_back(value); }
  void pop() { data_.pop_back(); }
  void swap(stack &other) { data_.swap(other.data_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    data_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  s21::list<T> data_;
};

}  // namespace s21

#endif
