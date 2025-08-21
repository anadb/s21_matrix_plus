#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_containersplus.h"

using namespace std;
using namespace s21;

class SetTest : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(SetTest, DefaultConstructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST_F(SetTest, InitializerListConstructor) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4, 5, 3, 4};

  EXPECT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  for (; s21_it != s21_set.end() && std_it != std_set.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST_F(SetTest, CopyConstructor) {
  s21::set<int> s21_original = {1, 2, 3, 4, 5};
  std::set<int> std_original = {1, 2, 3, 4, 5};

  s21::set<int> s21_copy(s21_original);
  std::set<int> std_copy(std_original);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_original.size(), std_original.size());

  auto s21_it = s21_copy.begin();
  auto std_it = std_copy.begin();
  for (; s21_it != s21_copy.end() && std_it != std_copy.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST_F(SetTest, MoveConstructor) {
  s21::set<int> s21_original = {1, 2, 3, 4, 5};
  std::set<int> std_original = {1, 2, 3, 4, 5};

  s21::set<int> s21_moved(std::move(s21_original));
  std::set<int> std_moved(std::move(std_original));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_original.size(), std_original.size());
  EXPECT_EQ(s21_original.empty(), std_original.empty());
}

TEST_F(SetTest, Insert) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  auto s21_result1 = s21_set.insert(5);
  auto std_result1 = std_set.insert(5);

  EXPECT_EQ(s21_result1.second, std_result1.second);
  EXPECT_EQ(*s21_result1.first, *std_result1.first);
  EXPECT_EQ(s21_set.size(), std_set.size());

  auto s21_result2 = s21_set.insert(5);
  auto std_result2 = std_set.insert(5);

  EXPECT_EQ(s21_result2.second, std_result2.second);
  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.insert(3);
  s21_set.insert(7);
  s21_set.insert(1);
  std_set.insert(3);
  std_set.insert(7);
  std_set.insert(1);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST_F(SetTest, Find) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  auto s21_it = s21_set.find(3);
  auto std_it = std_set.find(3);

  EXPECT_NE(s21_it, s21_set.end());
  EXPECT_NE(std_it, std_set.end());
  EXPECT_EQ(*s21_it, *std_it);

  auto s21_not_found = s21_set.find(10);
  auto std_not_found = std_set.find(10);

  EXPECT_EQ(s21_not_found, s21_set.end());
  EXPECT_EQ(std_not_found, std_set.end());
}

TEST_F(SetTest, Contains) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_set.contains(3), std_set.find(3) != std_set.end());
  EXPECT_EQ(s21_set.contains(10), std_set.find(10) != std_set.end());
}

TEST_F(SetTest, Erase) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  auto s21_it = s21_set.find(3);
  auto std_it = std_set.find(3);

  s21_set.erase(s21_it);
  std_set.erase(std_it);

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.contains(3), std_set.find(3) != std_set.end());
}

TEST_F(SetTest, Clear) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  s21_set.clear();
  std_set.clear();

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST_F(SetTest, Swap) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2 = {4, 5, 6};
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {4, 5, 6};

  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);

  EXPECT_EQ(s21_set1.size(), std_set1.size());
  EXPECT_EQ(s21_set2.size(), std_set2.size());
}

TEST_F(SetTest, Merge) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2 = {3, 4, 5};
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {3, 4, 5};

  s21_set1.merge(s21_set2);
  std_set1.insert(std_set2.begin(), std_set2.end());

  EXPECT_EQ(s21_set1.size(), std_set1.size());
}

TEST_F(SetTest, Iteration) {
  s21::set<int> s21_set = {5, 3, 7, 1, 9};
  std::set<int> std_set = {5, 3, 7, 1, 9};

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();

  for (; s21_it != s21_set.end() && std_it != std_set.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST_F(SetTest, ConstIteration) {
  const s21::set<int> s21_set = {1, 2, 3, 4, 5};
  const std::set<int> std_set = {1, 2, 3, 4, 5};

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();

  for (; s21_it != s21_set.end() && std_it != std_set.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST_F(SetTest, EmptySetOperations) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.begin(), s21_set.end());
  EXPECT_EQ(std_set.begin(), std_set.end());
}

TEST_F(SetTest, LargeSetOperations) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  for (int i = 0; i < 1000; ++i) {
    s21_set.insert(i);
    std_set.insert(i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());

  for (int i = 0; i < 1000; i += 10) {
    EXPECT_EQ(s21_set.contains(i), std_set.find(i) != std_set.end());
  }
}

TEST_F(SetTest, InsertMany) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  auto results = s21_set.insert_many(4, 5, 6);

  EXPECT_EQ(s21_set.size(), 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
