// #include "./include/s21_map.h"
#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_containersplus.h"
using namespace std;
using namespace s21;

template <typename S21MultiSet, typename StdMultiSet>
void AssertMultiSetsEqual(const S21MultiSet &s21ms, const StdMultiSet &stdms) {
  ASSERT_EQ(s21ms.size(), stdms.size());
  auto it1 = s21ms.begin();
  auto it2 = stdms.begin();
  for (; it1 != s21ms.end() && it2 != stdms.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(Multiset, DefaultConstructor) {
  s21::multiset<int> s21ms;
  std::multiset<int> stdms;
  AssertMultiSetsEqual(s21ms, stdms);
}

TEST(Multiset, InitializerListConstructor) {
  s21::multiset<int> s21ms{1, 2, 2, 3};
  std::multiset<int> stdms{1, 2, 2, 3};
  AssertMultiSetsEqual(s21ms, stdms);
}

TEST(Multiset, InsertAndOrder) {
  s21::multiset<int> s21ms;
  std::multiset<int> stdms;
  for (int v : {5, 1, 3, 3, 2}) {
    s21ms.insert(v);
    stdms.insert(v);
  }
  AssertMultiSetsEqual(s21ms, stdms);
}

TEST(Multiset, EraseByIterator) {
  s21::multiset<int> s21ms{1, 2, 2, 3};
  std::multiset<int> stdms{1, 2, 2, 3};
  auto it1 = s21ms.begin();
  auto it2 = stdms.begin();
  ++it1;
  ++it2;  // Point to first '2'
  s21ms.erase(it1);
  stdms.erase(it2);
  AssertMultiSetsEqual(s21ms, stdms);
}

TEST(Multiset, EraseByKey) {
  s21::multiset<int> s21ms{1, 2, 2, 3};
  std::multiset<int> stdms{1, 2, 2, 3};
  s21ms.erase(2);
  stdms.erase(2);
  AssertMultiSetsEqual(s21ms, stdms);
}

TEST(Multiset, FindAndCount) {
  s21::multiset<int> s21ms{1, 2, 2, 3};
  std::multiset<int> stdms{1, 2, 2, 3};
  ASSERT_EQ(s21ms.count(2), stdms.count(2));
  ASSERT_EQ(s21ms.count(4), stdms.count(4));
  ASSERT_EQ(*s21ms.find(2), *stdms.find(2));
}

TEST(Multiset, Contains) {
  s21::multiset<int> s21ms{1, 2, 3};
  ASSERT_TRUE(s21ms.contains(2));
  ASSERT_FALSE(s21ms.contains(4));
}

TEST(Multiset, ClearAndEmpty) {
  s21::multiset<int> s21ms{1, 2, 3};
  std::multiset<int> stdms{1, 2, 3};
  s21ms.clear();
  stdms.clear();
  AssertMultiSetsEqual(s21ms, stdms);
  ASSERT_TRUE(s21ms.empty());
}

TEST(Multiset, LowerUpperBound) {
  s21::multiset<int> s21ms{1, 2, 2, 3, 4};
  std::multiset<int> stdms{1, 2, 2, 3, 4};
  auto s21lb = s21ms.lower_bound(2);
  auto stdlb = stdms.lower_bound(2);
  ASSERT_EQ(*s21lb, *stdlb);
  auto s21ub = s21ms.upper_bound(2);
  auto stdub = stdms.upper_bound(2);
  ASSERT_EQ(*s21ub, *stdub);
}

TEST(Multiset, Swap) {
  s21::multiset<int> s21ms1{1, 2}, s21ms2{3, 4};
  std::multiset<int> stdms1{1, 2}, stdms2{3, 4};
  s21ms1.swap(s21ms2);
  stdms1.swap(stdms2);
  AssertMultiSetsEqual(s21ms1, stdms1);
  AssertMultiSetsEqual(s21ms2, stdms2);
}

TEST(MultiSetTest, InsertMany) {
  s21::multiset<int> s21_multiset = {1, 2, 3};
  auto results = s21_multiset.insert_many(3, 5, 6);

  EXPECT_EQ(s21_multiset.size(), 6);
}
