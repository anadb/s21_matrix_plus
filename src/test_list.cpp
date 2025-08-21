#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "s21_containersplus.h"

using namespace std;
using namespace s21;

TEST(S21ListTest, DefaultConstructor) {
  s21::list<int> s21_lst;
  std::list<int> std_lst;
  ASSERT_EQ(s21_lst.size(), std_lst.size());
  ASSERT_EQ(s21_lst.empty(), std_lst.empty());
}

TEST(S21ListTest, PushBackAndFront) {
  s21::list<int> s21_lst;
  std::list<int> std_lst;
  for (int i = 0; i < 5; ++i) {
    s21_lst.push_back(i);
    std_lst.push_back(i);
    ASSERT_EQ(s21_lst.back(), std_lst.back());
    ASSERT_EQ(s21_lst.size(), std_lst.size());
  }
}

TEST(S21ListTest, PopBack) {
  s21::list<int> s21_lst = {1, 2, 3};
  std::list<int> std_lst = {1, 2, 3};
  s21_lst.pop_back();
  std_lst.pop_back();
  ASSERT_EQ(s21_lst.size(), std_lst.size());
  ASSERT_EQ(s21_lst.back(), std_lst.back());
}

TEST(S21ListTest, PushPopFront) {
  s21::list<int> s21_lst;
  std::list<int> std_lst;
  for (int i = 0; i < 3; ++i) {
    s21_lst.push_back(i);
    std_lst.push_back(i);
  }
  s21_lst.pop_front();
  std_lst.pop_front();
  ASSERT_EQ(s21_lst.front(), std_lst.front());
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, Clear) {
  s21::list<int> s21_lst = {1, 2, 3};
  std::list<int> std_lst = {1, 2, 3};
  s21_lst.clear();
  std_lst.clear();
  ASSERT_EQ(s21_lst.size(), std_lst.size());
  ASSERT_EQ(s21_lst.empty(), std_lst.empty());
}

TEST(S21ListTest, InsertErase) {
  s21::list<int> s21_lst = {1, 2, 4};
  std::list<int> std_lst = {1, 2, 4};
  auto s21_it = s21_lst.at(2);
  auto std_it = std_lst.begin();
  std::advance(std_it, 2);
  s21_lst.insert(s21_it, 3);
  std_lst.insert(std_it, 3);

  // Compare all elements
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());

  // Erase the inserted element
  s21_it = s21_lst.at(2);
  std_it = std_lst.begin();
  std::advance(std_it, 2);
  s21_lst.erase(s21_it);
  std_lst.erase(std_it);

  s21_iter = s21_lst.begin();
  std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, InitializerListConstructor) {
  s21::list<int> s21_lst = {1, 2, 3, 4};
  std::list<int> std_lst = {1, 2, 3, 4};
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, Sort) {
  s21::list<int> s21_lst = {3, 1, 4, 1, 5, 9, 2};
  std::list<int> std_lst = {3, 1, 4, 1, 5, 9, 2};
  s21_lst.sort();
  std_lst.sort();
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, Reverse) {
  s21::list<int> s21_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  s21_lst.reverse();
  std_lst.reverse();
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, Unique) {
  s21::list<int> s21_lst = {1, 1, 2, 3, 3, 3, 4, 5, 5};
  std::list<int> std_lst = {1, 1, 2, 3, 3, 3, 4, 5, 5};
  s21_lst.unique();
  std_lst.unique();
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, Merge) {
  s21::list<int> s21_lst1 = {1, 3, 5};
  s21::list<int> s21_lst2 = {2, 4, 6};
  std::list<int> std_lst1 = {1, 3, 5};
  std::list<int> std_lst2 = {2, 4, 6};
  s21_lst1.merge(s21_lst2);
  std_lst1.merge(std_lst2);
  auto s21_iter = s21_lst1.begin();
  auto std_iter = std_lst1.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst1.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst1.size(), std_lst1.size());
  ASSERT_TRUE(s21_lst2.empty());
  ASSERT_TRUE(std_lst2.empty());
}

TEST(S21ListTest, Splice) {
  s21::list<int> s21_lst1 = {1, 2, 5};
  s21::list<int> s21_lst2 = {3, 4};
  std::list<int> std_lst1 = {1, 2, 5};
  std::list<int> std_lst2 = {3, 4};

  auto s21_pos = s21_lst1.at(2);
  auto std_pos = std_lst1.begin();
  std::advance(std_pos, 2);
  s21_lst1.splice(s21_pos, s21_lst2);
  std_lst1.splice(std_pos, std_lst2);

  auto s21_iter = s21_lst1.begin();
  auto std_iter = std_lst1.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst1.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst1.size(), std_lst1.size());
  ASSERT_TRUE(s21_lst2.empty());
  ASSERT_TRUE(std_lst2.empty());
}

TEST(S21ListTest, InsertMany) {
  s21::list<int> s21_lst = {1, 2, 5};
  std::list<int> std_lst = {1, 2, 5};

  // Insert multiple elements before position 2 (before 5)
  auto s21_pos = s21_lst.begin();
  ++s21_pos;
  ++s21_pos;

  auto std_pos = std_lst.begin();
  std::advance(std_pos, 2);

  s21_lst.insert_many(s21_pos, 3, 4);
  std_lst.insert(std_pos, 3);
  std_lst.insert(std_pos, 4);

  // Compare results
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, InsertManyFront) {
  s21::list<int> s21_lst = {4, 5, 6};
  std::list<int> std_lst = {4, 5, 6};

  s21_lst.insert_many_front(1, 2, 3);
  std_lst.insert(std_lst.begin(), 3);
  std_lst.insert(std_lst.begin(), 2);
  std_lst.insert(std_lst.begin(), 1);

  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, InsertManyFrontEmpty) {
  s21::list<int> s21_lst;

  // Insert into empty list
  s21_lst.insert_many_front(1, 2, 3);

  ASSERT_EQ(s21_lst.size(), 3);
  ASSERT_EQ(s21_lst.front(), 1);
  ASSERT_EQ(s21_lst.back(), 3);
}

TEST(S21ListTest, InsertManyFrontSingleArg) {
  s21::list<int> s21_lst = {2, 3};

  // Insert single element at front
  s21_lst.insert_many_front(1);

  ASSERT_EQ(s21_lst.size(), 3);
  ASSERT_EQ(s21_lst.front(), 1);
}

TEST(S21ListTest, InsertManyBack) {
  s21::list<int> s21_lst = {1, 2, 3};
  std::list<int> std_lst = {1, 2, 3};

  // Append multiple elements
  s21_lst.insert_many_back(4, 5, 6);
  std_lst.insert(std_lst.end(), 4);
  std_lst.insert(std_lst.end(), 5);
  std_lst.insert(std_lst.end(), 6);

  // Compare results
  auto s21_iter = s21_lst.begin();
  auto std_iter = std_lst.begin();
  for (; s21_iter.get_node() != nullptr && std_iter != std_lst.end();
       ++s21_iter, ++std_iter) {
    ASSERT_EQ(*s21_iter, *std_iter);
  }
  ASSERT_EQ(s21_lst.size(), std_lst.size());
}

TEST(S21ListTest, InsertManyBackEmpty) {
  s21::list<int> s21_lst;

  // Append to empty list
  s21_lst.insert_many_back(1, 2, 3);

  ASSERT_EQ(s21_lst.size(), 3);
  ASSERT_EQ(s21_lst.front(), 1);
  ASSERT_EQ(s21_lst.back(), 3);
}

TEST(S21ListTest, InsertManyBackSingleArg) {
  s21::list<int> s21_lst = {1, 2};

  // Append single element
  s21_lst.insert_many_back(3);

  ASSERT_EQ(s21_lst.size(), 3);
  ASSERT_EQ(s21_lst.back(), 3);
}
