#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "s21_containersplus.h"

using namespace std;

TEST(Function, at) {
  s21::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v.at(4), 4);
}

TEST(Function, brackets_overload) {
  s21::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v[4], 4);
}

TEST(Function, front) {
  s21::vector<int> v = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v.front(), -1);
}

TEST(Function, back) {
  s21::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v.back(), 8);
}

TEST(Function, data) {
  s21::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v.data(), &(v[0]));
}

TEST(Function, empty) {
  s21::vector<int> v;
  ASSERT_EQ(true, v.empty());
}

TEST(Function, not_empty) {
  s21::vector<int> v = {1, 2, 3};
  ASSERT_EQ(false, v.empty());
}

TEST(Function, size) {
  s21::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v.size(), 9);
}

TEST(Function, max_size) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(v_s21.max_size(), v_std.max_size());
}

TEST(Function, reserve) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};
  v_s21.reserve(10);
  v_std.reserve(10);
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, shrink_to_fit) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};

  v_s21.reserve(10);
  v_std.reserve(10);
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  v_s21.shrink_to_fit();
  v_std.shrink_to_fit();
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
}

TEST(Function, insert) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};
  v_s21.insert(v_s21.begin() + 3, 9);
  v_std.insert(v_std.begin() + 3, 9);
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, erase) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};
  v_s21.erase(v_s21.begin() + 3);
  v_std.erase(v_std.begin() + 3);
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, push_back) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};
  v_s21.push_back(10);
  v_std.push_back(10);
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, pop_back) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5};
  v_s21.pop_back();
  v_std.pop_back();
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, swap) {
  s21::vector<int> v1_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v1_std = {0, 1, 2, 3, 4, 5};

  s21::vector<int> v2_s21 = {6, 7, 8};
  std::vector<int> v2_std = {6, 7, 8};

  v1_s21.swap(v2_s21);
  v1_std.swap(v2_std);
  ASSERT_EQ(v1_s21.capacity(), v1_std.capacity());
  ASSERT_EQ(v1_s21.size(), v1_std.size());
  ASSERT_EQ(v2_s21.capacity(), v2_std.capacity());
  ASSERT_EQ(v2_s21.size(), v2_std.size());

  for (size_t i = 0; i < v1_std.size(); ++i) {
    ASSERT_EQ(v1_s21[i], v1_std[i]);
  }
  for (size_t i = 0; i < v2_std.size(); ++i) {
    ASSERT_EQ(v2_s21[i], v2_std[i]);
  }
}

TEST(Function, insert_many) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 8, 8, 8, 8, 3, 4, 5};
  v_s21.insert_many(v_s21.begin() + 3, 8, 8, 8, 8);
  v_s21.shrink_to_fit();
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}

TEST(Function, insert_many_back) {
  s21::vector<int> v_s21 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_std = {0, 1, 2, 3, 4, 5, 8, 8, 8, 8};
  v_s21.insert_many_back(8, 8, 8, 8);
  v_s21.shrink_to_fit();
  ASSERT_EQ(v_s21.capacity(), v_std.capacity());
  ASSERT_EQ(v_s21.size(), v_std.size());
  for (size_t i = 0; i < v_std.size(); ++i) {
    ASSERT_EQ(v_s21[i], v_std[i]);
  }
}
