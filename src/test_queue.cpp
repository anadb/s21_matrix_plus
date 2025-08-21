#include <gtest/gtest.h>

#include <iostream>

#include "s21_containersplus.h"
using namespace std;
using namespace s21;

#include <queue>

// Test default constructor and empty
TEST(S21QueueTest, DefaultConstructorAndEmpty) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  ASSERT_EQ(s21_q.empty(), std_q.empty());
  ASSERT_EQ(s21_q.size(), std_q.size());
}

// Test initializer list constructor
TEST(S21QueueTest, InitializerListConstructor) {
  s21::queue<int> s21_q{1, 2, 3};
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);
  ASSERT_EQ(s21_q.size(), std_q.size());
  ASSERT_EQ(s21_q.front(), std_q.front());
  ASSERT_EQ(s21_q.back(), std_q.back());
}

// Test push and pop
TEST(S21QueueTest, PushPop) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  for (int i = 0; i < 5; ++i) {
    s21_q.push(i);
    std_q.push(i);
  }
  while (!std_q.empty()) {
    ASSERT_EQ(s21_q.front(), std_q.front());
    s21_q.pop();
    std_q.pop();
  }
  ASSERT_EQ(s21_q.empty(), std_q.empty());
}

// Test copy constructor
TEST(S21QueueTest, CopyConstructor) {
  s21::queue<int> s21_q1{1, 2, 3};
  s21::queue<int> s21_q2(s21_q1);
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);
  while (!std_q.empty()) {
    ASSERT_EQ(s21_q2.front(), std_q.front());
    s21_q2.pop();
    std_q.pop();
  }
}

// Test move constructor
TEST(S21QueueTest, MoveConstructor) {
  s21::queue<int> s21_q1{1, 2, 3};
  s21::queue<int> s21_q2(std::move(s21_q1));
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);
  while (!std_q.empty()) {
    ASSERT_EQ(s21_q2.front(), std_q.front());
    s21_q2.pop();
    std_q.pop();
  }
}

// Test swap
TEST(S21QueueTest, Swap) {
  s21::queue<int> s21_q1{1, 2, 3};
  s21::queue<int> s21_q2{4, 5};
  s21_q1.swap(s21_q2);
  std::queue<int> std_q1, std_q2;
  std_q1.push(1);
  std_q1.push(2);
  std_q1.push(3);
  std_q2.push(4);
  std_q2.push(5);
  std::swap(std_q1, std_q2);
  while (!std_q1.empty()) {
    ASSERT_EQ(s21_q1.front(), std_q1.front());
    s21_q1.pop();
    std_q1.pop();
  }
  while (!std_q2.empty()) {
    ASSERT_EQ(s21_q2.front(), std_q2.front());
    s21_q2.pop();
    std_q2.pop();
  }
}

// Test emplace_back
TEST(S21QueueTest, EmplaceBack) {
  s21::queue<std::string> s21_q;
  std::queue<std::string> std_q;
  s21_q.emplace_back(5, 'a');
  std_q.emplace("aaaaa");
  ASSERT_EQ(s21_q.back(), std_q.back());
  ASSERT_EQ(s21_q.front(), std_q.front());
  ASSERT_EQ(s21_q.size(), std_q.size());
}

TEST(S21QueueTest, InsertManyBack) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);

  ASSERT_EQ(q.size(), 3);
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.back(), 3);
}

TEST(S21QueueTest, InsertManyBackEmpty) {
  s21::queue<int> q;
  q.insert_many_back(42);

  ASSERT_EQ(q.size(), 1);
  ASSERT_EQ(q.front(), 42);
  ASSERT_EQ(q.back(), 42);
}
