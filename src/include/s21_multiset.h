#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<value_type, true>::TreeIterator;
  using const_iterator = typename tree<value_type, true>::TreeConstIterator;
  using size_type = size_t;

  // Constructors
  multiset() : tree_() {}

  multiset(std::initializer_list<value_type> const &items) : tree_() {
    for (const auto &item : items) {
      insert(item);
    }
  }

  multiset(const multiset &ms) : tree_(ms.tree_) {}

  multiset(multiset &&ms) noexcept : tree_(std::move(ms.tree_)) {}

  ~multiset() = default;

  multiset &operator=(const multiset &ms) {
    if (this != &ms) {
      tree_ = ms.tree_;
    }
    return *this;
  }

  multiset &operator=(multiset &&ms) noexcept {
    if (this != &ms) {
      tree_ = std::move(ms.tree_);
    }
    return *this;
  }

  multiset &operator=(std::initializer_list<value_type> const &items) {
    tree_.clear();
    for (const auto &item : items) {
      insert(item);
    }
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

  iterator insert(const value_type &value) {
    tree_.insert(value);
    return tree_.find(value);
  }

  void erase(iterator pos) { tree_.erase(pos); }

  size_type erase(const key_type &key) {
    size_type count = 0;
    iterator it = find(key);
    while (it != end() && *it == key) {
      iterator next = it;
      ++next;
      tree_.erase(it);
      it = next;
      ++count;
    }
    return count;
  }

  void swap(multiset &other) { std::swap(tree_, other.tree_); }

  void merge(multiset &other) { tree_.merge(other.tree_); }

  // Lookup
  iterator find(const key_type &key) { return tree_.find(key); }
  const_iterator find(const key_type &key) const { return tree_.find(key); }

  bool contains(const key_type &key) { return tree_.find(key) != tree_.end(); }
  bool contains(const key_type &key) const {
    return tree_.find(key) != tree_.end();
  }

  size_type count(const key_type &key) const {
    size_type count = 0;
    const_iterator it = find(key);
    while (it != end() && *it == key) {
      ++count;
      ++it;
    }
    return count;
  }

  iterator lower_bound(const key_type &key) {
    iterator it = begin();
    while (it != end() && *it < key) {
      ++it;
    }
    return it;
  }

  const_iterator lower_bound(const key_type &key) const {
    const_iterator it = begin();
    while (it != end() && *it < key) {
      ++it;
    }
    return it;
  }

  iterator upper_bound(const key_type &key) {
    iterator it = begin();
    while (it != end() && *it <= key) {
      ++it;
    }
    return it;
  }

  const_iterator upper_bound(const key_type &key) const {
    const_iterator it = begin();
    while (it != end() && *it <= key) {
      ++it;
    }
    return it;
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return {lower_bound(key), upper_bound(key)};
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &key) const {
    return {lower_bound(key), upper_bound(key)};
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> result;
    (result.push_back({insert(std::forward<Args>(args)), true}), ...);
    return result;
  }

 private:
  tree<value_type, true> tree_;
};
}  // namespace s21

#endif
