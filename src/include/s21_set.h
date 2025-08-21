#ifndef S21_SET_H_
#define S21_SET_H_

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<value_type>::TreeIterator;
  using const_iterator = typename tree<value_type>::TreeConstIterator;
  using size_type = size_t;

  set() : tree_() {}
  set(std::initializer_list<value_type> const &items) : tree_(items) {}
  set(const set &s) : tree_(s.tree_) {}
  set(set &&s) noexcept : tree_(std::move(s.tree_)) {}
  ~set() = default;

  set &operator=(set &&s) noexcept {
    tree_ = std::move(s.tree_);
    return *this;
  }

  iterator begin() { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator begin() const { return tree_.begin(); }
  const_iterator end() const { return tree_.end(); }

  bool empty() const { return tree_.empty(); }
  size_type size() const { return tree_.size(); }
  size_type max_size() const { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    auto it = tree_.find(value);
    if (it != tree_.end()) {
      return {it, false};
    }
    tree_.insert(value);
    it = tree_.find(value);
    return {it, true};
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void swap(set &other) { std::swap(tree_, other.tree_); }

  void merge(set &other) { tree_.merge(other.tree_); }

  iterator find(const key_type &key) { return tree_.find(key); }
  bool contains(const key_type &key) { return tree_.find(key) != tree_.end(); }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  tree<value_type, false> tree_;
};
}  // namespace s21

#endif
