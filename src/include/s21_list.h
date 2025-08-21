#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 private:
  struct node_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  list() : head_(nullptr), tail_(nullptr), size_(0) {};
  list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    while (size_ < n) {
      push_back(0);
    }
  }
  list(std::initializer_list<value_type> const &items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (auto &item : items) {
      push_back(item);
    }
  }
  list(const list &l) : list() {
    const_iterator it = l.begin();
    for (size_type i = 0; i < l.size(); ++i) {
      push_back(*it);
      ++it;
    }
  }
  list(list &&l) noexcept : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  list &operator=(list &&l) noexcept {
    if (this != &l) {
      clear();
      head_ = l.head_;
      tail_ = l.tail_;
      size_ = l.size_;

      l.head_ = nullptr;
      l.tail_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  ~list() { clear(); }
  class ListIterator {
   private:
    node_ *current;

   public:
    ListIterator(node_ *node) : current(node) {};
    reference operator*() { return current->data; };
    ListIterator &operator++() {
      current = current->next;
      return *this;
    };
    ListIterator &operator--() {
      current = current->prev;
      return *this;
    };
    node_ *get_node() const { return current; }
    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }
  };

  class ListConstIterator {
   private:
    const node_ *current;

   public:
    ListConstIterator(const node_ *node) : current(node) {};
    ListConstIterator(const ListIterator &it) : current(it.get_node()) {}
    const_reference operator*() const { return current->data; };
    ListConstIterator &operator++() {
      current = current->next;
      return *this;
    };
    const node_ *get_node() const { return current; }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() { return head_; };
  const_iterator begin() const { return head_; };
  iterator end() { return tail_; };
  const_iterator end() const { return tail_; };

  void push_front(const_reference value) {
    node_ *new_node = new node_(value, nullptr, head_);
    if (head_) {
      head_->prev = new_node;
    } else {
      tail_ = new_node;
    }
    head_ = new_node;
    ++size_;
  }

  void push_back(const_reference value) {
    node_ *new_node = new node_(value, tail_, nullptr);
    if (tail_) {
      tail_->next = new_node;
    } else {
      head_ = new_node;
    }
    tail_ = new_node;
    ++size_;
  }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }

    node_ *temp = tail_;
    if (head_ == tail_) {
      head_ = tail_ = nullptr;
    } else {
      tail_ = tail_->prev;
      tail_->next = nullptr;
    }
    delete temp;
    --size_;
  }
  size_type size() { return size_; }
  size_type size() const { return size_; };
  size_type max_size() const { return std::numeric_limits<size_type>::max(); }
  reference front() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return head_->data;
  }
  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return head_->data;
  }
  reference back() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return tail_->data;
  }
  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
    return tail_->data;
  }
  bool empty() const { return size_ == 0; };
  void pop_front() {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }

    node_ *temp = head_;
    if (head_ == tail_) {
      head_ = tail_ = nullptr;
    } else {
      head_ = head_->next;
      head_->prev = nullptr;
    }
    delete temp;
    --size_;
  }
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  iterator at(size_t index) {
    if (index >= size_) return end();

    node_ *current = head_;
    for (size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return iterator(current);
  }

  iterator insert(iterator pos, const_reference value) {
    node_ *current = pos.get_node();
    node_ *new_node = new node_(value, current->prev, current);
    current->prev->next = new_node;
    current->prev = new_node;
    ++size_;
    return iterator(new_node);
  }

  void erase(iterator pos) {
    node_ *current = pos.get_node();
    if (current == head_ && current == tail_) {
      head_ = tail_ = nullptr;
    } else if (current == head_) {
      head_ = current->next;
      if (head_) head_->prev = nullptr;
    } else if (current == tail_) {
      tail_ = current->prev;
      if (tail_) tail_->next = nullptr;
    } else {
      current->prev->next = current->next;
      current->next->prev = current->prev;
    }
    delete current;
    --size_;
  }

  void swap(list &other) {
    list<value_type> temp(std::move(*this));
    *this = std::move(other);
    other = std::move(temp);
  }

  void swap_elements(iterator pos1, iterator pos2) {
    value_type temp = pos1.get_node()->data;
    pos1.get_node()->data = pos2.get_node()->data;
    pos2.get_node()->data = temp;
  }
  void sort() {
    bool swapped;
    do {
      swapped = false;
      for (iterator it = begin(); it.get_node() != tail_; ++it) {
        if (*it > *(++iterator(it.get_node()))) {
          swap_elements(it, iterator(it.get_node()->next));
          swapped = true;
        }
      }
    } while (swapped);
  }

  void reverse() {
    if (size_ <= 1) return;

    iterator forward_it = begin();
    iterator backward_it = end();

    while (forward_it.get_node() != backward_it.get_node() &&
           forward_it.get_node()->prev != backward_it.get_node()) {
      swap_elements(forward_it, backward_it);
      ++forward_it;
      --backward_it;
    }
  }

  void unique() {
    if (size() < 2) return;

    iterator prev = begin();
    iterator curr = prev;
    ++curr;

    while (curr.get_node() != nullptr) {
      if (*curr == *prev) {
        erase(curr);
        curr = prev;
        ++curr;
      } else {
        prev = curr;
        ++curr;
      }
    }
  }

  void merge(list &other) {
    if (this == &other) return;

    list merged;
    iterator it1 = begin();
    iterator it2 = other.begin();

    while (it1.get_node() != nullptr && it2.get_node() != nullptr) {
      if (*it1 < *it2) {
        merged.push_back(*it1);
        ++it1;
      } else {
        merged.push_back(*it2);
        ++it2;
      }
    }

    while (it1.get_node() != nullptr) {
      merged.push_back(*it1);
      ++it1;
    }

    while (it2.get_node() != nullptr) {
      merged.push_back(*it2);
      ++it2;
    }

    swap(merged);
    other.clear();
  }

  void splice(const_iterator pos, list &other) {
    if (this == &other || other.empty()) {
      return;
    }

    node_ *pos_node = const_cast<node_ *>(pos.get_node());
    node_ *other_first = other.head_;
    node_ *other_last = other.tail_;

    if (pos_node == head_) {
      other_last->next = head_;
      if (head_) head_->prev = other_last;
      head_ = other_first;
    } else if (pos_node == nullptr) {
      tail_->next = other_first;
      other_first->prev = tail_;
      tail_ = other_last;
    } else {
      other_first->prev = pos_node->prev;
      pos_node->prev->next = other_first;
      other_last->next = pos_node;
      pos_node->prev = other_last;
    }

    size_ += other.size_;
    other.size_ = 0;

    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  iterator insert_many(const_iterator pos,
                       std::initializer_list<value_type> items) {
    iterator it = iterator(const_cast<node_ *>(pos.get_node()));
    for (auto rit = items.end(); rit != items.begin();) {
      --rit;
      it = insert(it, *rit);
    }
    return it;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    const value_type items[] = {args...};
    iterator it = iterator(const_cast<node_ *>(pos.get_node()));
    for (size_t i = sizeof...(Args); i > 0; --i) {
      it = insert(it, items[i - 1]);
    }
    return it;
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    const value_type items[] = {args...};
    for (size_t i = sizeof...(Args); i > 0; --i) {
      push_front(items[i - 1]);
    }
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    const value_type items[] = {args...};
    for (size_t i = 0; i < sizeof...(Args); ++i) {
      push_back(items[i]);
    }
  }

 private:
  struct node_ {
    value_type data;
    node_ *prev;
    node_ *next;

    node_(const_reference val, node_ *p = nullptr, node_ *n = nullptr)
        : data(val), prev(p), next(n) {};
  };
  node_ *head_;
  node_ *tail_;
  size_type size_;
};
};  // namespace s21

#endif
