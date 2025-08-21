#include <gtest/gtest.h>

#include <stack>

#include "s21_containersplus.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }
}

TEST(StackTest, PushPopTop) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  for (int i = 0; i < 10; ++i) {
    s21_stack.push(i);
    std_stack.push(i);
    EXPECT_EQ(s21_stack.top(), std_stack.top());
  }
  for (int i = 9; i >= 0; --i) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s21_stack{1, 2, 3, 4};
  s21::stack<int> s21_copy(s21_stack);
  std::stack<int> std_stack;
  std::stack<int> std_copy;
  for (int i : {1, 2, 3, 4}) std_stack.push(i);
  std_copy = std_stack;
  while (!s21_copy.empty() && !std_copy.empty()) {
    EXPECT_EQ(s21_copy.top(), std_copy.top());
    s21_copy.pop();
    std_copy.pop();
  }
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  s21::stack<int> s21_moved(std::move(s21_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  while (!s21_moved.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_moved.top(), std_stack.top());
    s21_moved.pop();
    std_stack.pop();
  }
}

TEST(StackTest, Swap) {
  s21::stack<int> s21_a{1, 2, 3};
  s21::stack<int> s21_b{4, 5};
  std::stack<int> std_a, std_b;
  for (int i : {1, 2, 3}) std_a.push(i);
  for (int i : {4, 5}) std_b.push(i);
  s21_a.swap(s21_b);
  std_a.swap(std_b);
  while (!s21_a.empty() && !std_a.empty()) {
    EXPECT_EQ(s21_a.top(), std_a.top());
    s21_a.pop();
    std_a.pop();
  }
  while (!s21_b.empty() && !std_b.empty()) {
    EXPECT_EQ(s21_b.top(), std_b.top());
    s21_b.pop();
    std_b.pop();
  }
}

TEST(S21StackTest, InsertManyBack) {
  s21::stack<int> s;
  s.insert_many_back(1, 2, 3);

  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.top(), 3);
}

TEST(S21StackTest, InsertManyBackEmpty) {
  s21::stack<int> s;
  s.insert_many_back(42);

  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.top(), 42);
}
