#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 private:
  struct node;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  map() : tree_() {};
  map(const map &m) : tree_(m.tree_) {}
  map(map &&m) noexcept : tree_(std::move(m.tree_)) {}
  map(std::initializer_list<value_type> const &items) : tree_() {
    for (const auto &item : items) {
      insert(item);
    }
  }

  map &operator=(map &&m) noexcept {
    if (this != &m) {
      tree_ = std::move(m.tree_);
    }
    return *this;
  }

  map &operator=(std::initializer_list<value_type> const &items) {
    tree_ = tree<node>();
    for (const auto &item : items) {
      insert(item);
    }
    return *this;
  }

  ~map() = default;

  class MapIterator {
   private:
    typename tree<node>::TreeIterator tree_it_;

   public:
    MapIterator() : tree_it_(nullptr) {}
    MapIterator(typename tree<node>::TreeIterator it) : tree_it_(it) {}
    value_type &operator*() { return (*tree_it_).data; }

    value_type *operator->() { return &((*tree_it_).data); }

    bool operator!=(const MapIterator &other) const {
      return tree_it_ != other.tree_it_;
    }
    bool operator==(const MapIterator &other) const {
      return tree_it_ == other.tree_it_;
    }

    bool operator==(const std::nullptr_t &) const {
      return tree_it_ == nullptr;
    }
    bool operator!=(const std::nullptr_t &) const {
      return tree_it_ != nullptr;
    }
    typename tree<node>::TreeIterator get_tree_iterator() const {
      return tree_it_;
    }
  };

  class MapConstIterator {
   private:
    typename tree<node>::TreeConstIterator tree_it_;

   public:
    MapConstIterator(typename tree<node>::TreeConstIterator it)
        : tree_it_(it) {}
    const value_type &operator*() const { return (*tree_it_).data; }
    const value_type *operator->() const { return &((*tree_it_).data); }

    bool operator==(const std::nullptr_t &) const {
      return tree_it_ == nullptr;
    }
    bool operator!=(const std::nullptr_t &) const {
      return tree_it_ != nullptr;
    }
    bool operator!=(const MapIterator &other) const {
      return tree_it_ != other.tree_it_;
    }
    bool operator==(const MapIterator &other) const {
      return tree_it_ == other.tree_it_;
    }
  };

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  iterator begin() { return MapIterator(tree_.begin()); }
  iterator end() { return MapIterator(tree_.end()); }
  const_iterator begin() const { return MapConstIterator(tree_.begin()); }
  const_iterator end() const { return MapConstIterator(tree_.end()); }

  iterator find(const key_type &key) {
    node search_node(key, mapped_type());
    return MapIterator(tree_.find(search_node));
  }

  const_iterator find(const key_type &key) const {
    node search_node(key, mapped_type());
    return MapConstIterator(tree_.find(search_node));
  }

  T &at(const Key &key) {
    node search_node(key, T());
    auto it = tree_.find(search_node);
    if (it == nullptr) {
      throw std::out_of_range("Key not found");
    }
    return (*it).data.second;
  }

  T &operator[](const Key &key) {
    auto it = find(key);
    if (it == end()) {
      auto result = insert(key, T());
      return result.first->second;
    }
    return it->second;
  }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    node search_node(value.first, value.second);
    auto it = tree_.find(search_node);
    if (it != nullptr) {
      return {iterator(it), false};
    } else {
      tree_.insert(search_node);
      auto inserted_it = tree_.find(search_node);
      return {iterator(inserted_it), true};
    }
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    auto it = find(key);
    if (it != end()) {
      return {it, false};
    }
    node new_node(key, obj);
    tree_.insert(new_node);
    auto inserted_it = tree_.find(new_node);
    return {iterator(inserted_it), true};
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    node search_node(key, obj);
    auto it = tree_.find(search_node);
    if (it != nullptr) {
      (*it).data.second = obj;
      return {iterator(it), false};
    } else {
      tree_.insert(search_node);
      auto inserted_it = tree_.find(search_node);
      return {iterator(inserted_it), true};
    }
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    tree_.erase(pos.get_tree_iterator());
  }

  void swap(map &other) { std::swap(tree_, other.tree_); }

  void merge(map &other) {
    if (this == &other) return;
    tree_.merge(other.tree_);
  }

  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  bool contains(const Key &key) const {
    node search_node(key, mapped_type());
    return tree_.find(search_node) != nullptr;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  struct node {
    value_type data;
    node(const key_type &k, const mapped_type &v) : data(k, v) {}
    bool operator<(const node &other) const {
      return data.first < other.data.first;
    }
    bool operator>(const node &other) const {
      return data.first > other.data.first;
    }
    bool operator==(const node &other) const {
      return data.first == other.data.first;
    }
  };

  tree<node, false> tree_;
};
}  // namespace s21

#endif
