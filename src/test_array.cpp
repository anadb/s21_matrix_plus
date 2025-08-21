#include <gtest/gtest.h>

#include <array>

#include "s21_containersplus.h"

TEST(S21ArrayTest, DefaultConstructor) {
  s21::array<int, 3> s21arr;
  std::array<int, 3> stdarr{};
  for (size_t i = 0; i < 3; ++i) ASSERT_EQ(s21arr[i], stdarr[i]);
}

TEST(S21ArrayTest, InitializerListConstructor) {
  s21::array<int, 3> s21arr{1, 2, 3};
  std::array<int, 3> stdarr{1, 2, 3};
  for (size_t i = 0; i < 3; ++i) ASSERT_EQ(s21arr[i], stdarr[i]);
}

TEST(S21ArrayTest, AtAndOperator) {
  s21::array<int, 3> s21arr{4, 5, 6};
  std::array<int, 3> stdarr{4, 5, 6};
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(s21arr.at(i), stdarr.at(i));
    ASSERT_EQ(s21arr[i], stdarr[i]);
  }
  ASSERT_THROW(s21arr.at(3), std::out_of_range);
}

TEST(S21ArrayTest, FrontBackData) {
  s21::array<int, 3> s21arr{7, 8, 9};
  std::array<int, 3> stdarr{7, 8, 9};
  ASSERT_EQ(s21arr.front(), stdarr.front());
  ASSERT_EQ(s21arr.back(), stdarr.back());
  ASSERT_EQ(*s21arr.data(), *stdarr.data());
}

TEST(S21ArrayTest, Iterators) {
  s21::array<int, 3> s21arr{1, 2, 3};
  std::array<int, 3> stdarr{1, 2, 3};
  auto s21it = s21arr.begin();
  auto stdit = stdarr.begin();
  for (; s21it != s21arr.end() && stdit != stdarr.end(); ++s21it, ++stdit)
    ASSERT_EQ(*s21it, *stdit);
}

TEST(S21ArrayTest, Capacity) {
  s21::array<int, 3> s21arr{1, 2, 3};
  std::array<int, 3> stdarr{1, 2, 3};
  ASSERT_EQ(s21arr.empty(), stdarr.empty());
  ASSERT_EQ(s21arr.size(), stdarr.size());
  ASSERT_EQ(s21arr.max_size(), stdarr.max_size());
}

TEST(S21ArrayTest, Fill) {
  s21::array<int, 3> s21arr;
  std::array<int, 3> stdarr;
  s21arr.fill(42);
  stdarr.fill(42);
  for (size_t i = 0; i < 3; ++i) ASSERT_EQ(s21arr[i], stdarr[i]);
}

TEST(S21ArrayTest, Swap) {
  s21::array<int, 3> s21arr1{1, 2, 3}, s21arr2{4, 5, 6};
  std::array<int, 3> stdarr1{1, 2, 3}, stdarr2{4, 5, 6};
  s21arr1.swap(s21arr2);
  stdarr1.swap(stdarr2);
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(s21arr1[i], stdarr1[i]);
    ASSERT_EQ(s21arr2[i], stdarr2[i]);
  }
}
