#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 private:
  s21::list<T> list_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() = default;
  queue(std::initializer_list<value_type> const &items) : list_(items) {}
  queue(const queue &q) : list_(q.list_) {}
  queue(queue &&q) noexcept : list_(std::move(q.list_)) {}

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      list_ = std::move(q.list_);
    }
    return *this;
  }

  reference front() { return list_.front(); }
  const_reference front() const { return list_.front(); }
  reference back() { return list_.back(); }
  const_reference back() const { return list_.back(); }

  bool empty() const { return list_.empty(); }
  size_type size() const { return list_.size(); }

  void push(const_reference value) { list_.push_back(value); }
  void pop() { list_.pop_front(); }
  void swap(queue &other) { list_.swap(other.list_); }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    list_.push_back(value_type(std::forward<Args>(args)...));
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    list_.insert_many_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif
