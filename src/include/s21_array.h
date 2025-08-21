#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <stdexcept>

#include "s21_vector.h"

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array() : data_(N) {}

  array(std::initializer_list<value_type> init) : data_(N) {
    size_type i = 0;
    for (auto it = init.begin(); it != init.end() && i < N; ++it, ++i) {
      data_[i] = *it;
    }
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("array index out of range");
    return data_[pos];
  }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }
  reference front() { return data_[0]; }
  reference back() { return data_[N - 1]; }
  iterator data() { return &data_[0]; }
  const_iterator data() const { return &data_[0]; }

  iterator begin() { return &data_[0]; }
  iterator end() { return &data_[0] + N; }
  const_iterator begin() const { return &data_[0]; }
  const_iterator end() const { return &data_[0] + N; }

  constexpr bool empty() const { return N == 0; }
  constexpr size_type size() const { return N; }
  constexpr size_type max_size() const { return N; }

  void fill(const value_type &value) {
    for (size_type i = 0; i < N; ++i) data_[i] = value;
  }
  void swap(array &other) {
    for (size_type i = 0; i < N; ++i) std::swap(data_[i], other.data_[i]);
  }

 private:
  s21::vector<value_type> data_;
};

}  // namespace s21

#endif
