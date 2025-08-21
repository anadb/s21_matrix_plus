#ifndef S21_TREE_H_
#define S21_TREE_H_
#include <iostream>
#include <limits>
#include <utility>
using namespace std;
namespace s21 {
template <typename T, bool AllowDuplicates = false>
class tree {
 private:
  struct node;

 public:
  using tree_data_type = T;
  using size_type = size_t;

  tree() : parent_(nullptr), size_(0) {};
  tree(const tree &other) : parent_(copy(other.parent_)), size_(other.size_) {}
  tree(tree &&other) noexcept : parent_(other.parent_), size_(other.size_) {
    other.parent_ = nullptr;
    other.size_ = 0;
  }

  tree(std::initializer_list<tree_data_type> const &items)
      : parent_(nullptr), size_(0) {
    for (const auto &item : items) {
      insert(item);
    }
  }

  tree &operator=(const tree &other) {
    if (this != &other) {
      clear(parent_);
      parent_ = copy(other.parent_, nullptr);
      size_ = other.size_;
    }
    return *this;
  }

  tree &operator=(tree &&other) noexcept {
    if (this != &other) {
      clear(parent_);
      parent_ = other.parent_;
      size_ = other.size_;
      other.parent_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  tree &operator=(std::initializer_list<tree_data_type> const &items) {
    clear(parent_);
    parent_ = nullptr;
    size_ = 0;
    for (const auto &item : items) {
      insert(item);
    }
    return *this;
  }

  ~tree() { clear(parent_); }

  void insert(tree_data_type data) {
    bool inserted = false;
    parent_ = insertHelper(data, parent_, nullptr, inserted);
    if (inserted) size_++;
  }

  class TreeIterator {
   private:
    node *current;

   public:
    TreeIterator(node *node) : current(node) {};
    TreeIterator() : current(nullptr) {}
    tree_data_type &operator*() { return current->data; };
    TreeIterator &operator++() {
      if (!current) return *this;
      if (current->right) {
        current = current->right;
        while (current->left) current = current->left;
      } else {
        node *p = current->parent;
        while (p && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }
    TreeIterator &go_left() {
      current = current->left;
      return *this;
    };
    TreeIterator &go_right() {
      current = current->right;
      return *this;
    }

    bool operator==(const TreeIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const TreeIterator &other) const {
      return current != other.current;
    }

    bool operator==(const std::nullptr_t &) const { return current == nullptr; }
    bool operator!=(const std::nullptr_t &) const { return current != nullptr; }
  };

  class TreeConstIterator {
   private:
    const node *current;

   public:
    TreeConstIterator(const node *node) : current(node) {};
    const tree_data_type &operator*() const { return current->data; };
    TreeConstIterator &operator++() {
      if (!current) return *this;
      if (current->right) {
        current = current->right;
        while (current->left) current = current->left;
      } else {
        const node *p = current->parent;
        while (p && current == p->right) {
          current = p;
          p = p->parent;
        }
        current = p;
      }
      return *this;
    }

    bool operator==(const TreeConstIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const TreeConstIterator &other) const {
      return current != other.current;
    }

    bool operator==(const std::nullptr_t &) const { return current == nullptr; }
    bool operator!=(const std::nullptr_t &) const { return current != nullptr; }
  };

  TreeIterator begin() {
    node *cur = parent_;
    if (!cur) return TreeIterator(nullptr);
    while (cur->left) cur = cur->left;
    return TreeIterator(cur);
  }

  TreeConstIterator begin() const {
    const node *cur = parent_;
    if (!cur) return TreeConstIterator(nullptr);
    while (cur->left) cur = cur->left;
    return TreeConstIterator(cur);
  }

  TreeIterator end() { return TreeIterator(nullptr); }
  TreeConstIterator end() const { return TreeConstIterator(nullptr); }

  TreeIterator find(tree_data_type data) { return findHelper(data, parent_); }
  TreeConstIterator find(tree_data_type data) const {
    return findHelper(data, parent_);
  }
  void erase(TreeIterator pos) {
    parent_ = eraseHelper(parent_, *pos);
    --size_;
  }

  void clear() {
    clear(parent_);
    parent_ = nullptr;
    size_ = 0;
  }

  size_type size() const { return size_; };

  bool empty() const { return size_ == 0; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(node);
  }

  void merge(tree &other) {
    if (this == &other) return;

    TreeIterator it = other.begin();
    TreeIterator end = other.end();

    while (it != end) {
      tree_data_type data = *it;
      ++it;

      if (!findHelper(data, parent_)) {
        TreeIterator to_erase = other.find(data);
        if (to_erase != nullptr) {
          other.erase(to_erase);
          bool inserted = false;
          parent_ = insertHelper(data, parent_, nullptr, inserted);
          if (inserted) size_++;
        }
      }
    }
  }

 private:
  struct node {
    tree_data_type data;
    node *left;
    node *right;
    node *parent;
    node(tree_data_type d, node *l = nullptr, node *r = nullptr,
         node *p = nullptr)
        : data(d), left(l), right(r), parent(p) {};
  };
  node *parent_;
  size_type size_;

  node *insertHelper(tree_data_type data, node *current, node *parent,
                     bool &inserted) {
    if (current == nullptr) {
      inserted = true;
      return new node(data, nullptr, nullptr, parent);
    }
    if (data < current->data) {
      current->left = insertHelper(data, current->left, current, inserted);
    } else if (data > current->data) {
      current->right = insertHelper(data, current->right, current, inserted);
    } else if constexpr (AllowDuplicates) {
      current->right = insertHelper(data, current->right, current, inserted);
    }
    return current;
  }

  node *findHelper(tree_data_type data, node *current) {
    if (!current) return nullptr;
    if (data < current->data) {
      return findHelper(data, current->left);
    } else if (data > current->data) {
      return findHelper(data, current->right);
    } else {
      return current;
    }
  }

  node *findHelper(tree_data_type data, node *current) const {
    if (!current) return nullptr;
    if (data < current->data) {
      return findHelper(data, current->left);
    } else if (data > current->data) {
      return findHelper(data, current->right);
    } else {
      return current;
    }
  }

  node *eraseHelper(node *current, tree_data_type data) {
    if (!current) return nullptr;
    if (data < current->data) {
      current->left = eraseHelper(current->left, data);
      if (current->left) current->left->parent = current;
    } else if (data > current->data) {
      current->right = eraseHelper(current->right, data);
      if (current->right) current->right->parent = current;
    } else {
      if (!current->left) {
        node *right = current->right;
        if (right) right->parent = current->parent;
        delete current;
        return right;
      } else if (!current->right) {
        node *left = current->left;
        if (left) left->parent = current->parent;
        delete current;
        return left;
      } else {
        node *succ = current->right;
        while (succ->left) succ = succ->left;
        current->right = eraseHelper(current->right, succ->data);
        if (current->right) current->right->parent = current;

        node *new_node = new node(succ->data, current->left, current->right,
                                  current->parent);
        if (new_node->left) new_node->left->parent = new_node;
        if (new_node->right) new_node->right->parent = new_node;

        delete current;
        return new_node;
      }
    }
    return current;
  }

  node *copy(node *current, node *parent = nullptr) {
    if (!current) return nullptr;
    node *new_node = new node(current->data, nullptr, nullptr, parent);
    new_node->left = copy(current->left, new_node);
    new_node->right = copy(current->right, new_node);
    return new_node;
  }

  void clear(node *current) {
    if (current) {
      clear(current->left);
      clear(current->right);
      delete current;
      current = nullptr;
    }
  }
};
}  // namespace s21

#endif
