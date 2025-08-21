#include <gtest/gtest.h>

#include <map>

#include "s21_containersplus.h"

namespace {

TEST(MapTest, DefaultConstructor) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.at(1), std_map.at(1));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
  EXPECT_EQ(s21_map.at(3), std_map.at(3));
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_copy(s21_map);

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_copy(std_map);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.at(1), std_copy.at(1));
  EXPECT_EQ(s21_copy.at(2), std_copy.at(2));
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_moved(std::move(s21_map));

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_moved(std::move(std_map));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_moved.at(1), std_moved.at(1));
  EXPECT_EQ(s21_moved.at(2), std_moved.at(2));
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapTest, MoveAssignment) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  s21::map<int, std::string> s21_moved;
  s21_moved = std::move(s21_map);

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_moved;
  std_moved = std::move(std_map);

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_moved.at(1), std_moved.at(1));
  EXPECT_EQ(s21_moved.at(2), std_moved.at(2));
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapTest, At) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};

  EXPECT_EQ(s21_map.at(1), std_map.at(1));
  EXPECT_EQ(s21_map.at(2), std_map.at(2));
  EXPECT_THROW(s21_map.at(3), std::out_of_range);
  EXPECT_THROW(std_map.at(3), std::out_of_range);
}

TEST(MapTest, SquareBrackets) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};

  EXPECT_EQ(s21_map[1], std_map[1]);
  EXPECT_EQ(s21_map[2], std_map[2]);

  EXPECT_EQ(s21_map[3], std_map[3]);
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapTest, InsertByValue) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_res = s21_map.insert({1, "one"});
  auto std_res = std_map.insert({1, "one"});

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_res.first->first, std_res.first->first);
  EXPECT_EQ(s21_res.first->second, std_res.first->second);

  // Insert existing key
  s21_res = s21_map.insert({1, "ONE"});
  std_res = std_map.insert({1, "ONE"});

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_res.first->first, std_res.first->first);
  EXPECT_EQ(s21_res.first->second, std_res.first->second);
  EXPECT_EQ(s21_map.at(1), std_map.at(1));
}

TEST(MapTest, InsertByKeyValue) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_res = s21_map.insert(1, "one");
  auto std_res = std_map.insert({1, "one"});

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_res.first->first, std_res.first->first);
  EXPECT_EQ(s21_res.first->second, std_res.first->second);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  // Insert new key
  auto s21_res = s21_map.insert_or_assign(1, "one");
  auto std_res = std_map.insert_or_assign(1, "one");

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_res.first->first, std_res.first->first);
  EXPECT_EQ(s21_res.first->second, std_res.first->second);

  // Assign existing key
  s21_res = s21_map.insert_or_assign(1, "ONE");
  std_res = std_map.insert_or_assign(1, "ONE");

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_res.first->first, std_res.first->first);
  EXPECT_EQ(s21_res.first->second, std_res.first->second);
  EXPECT_EQ(s21_map.at(1), std_map.at(1));
}

TEST(MapTest, Erase) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  s21_map.erase(s21_map.find(2));

  EXPECT_EQ(s21_map.size(), 2);
  EXPECT_EQ(s21_map.contains(2), false);
  EXPECT_EQ(s21_map.contains(1), true);
  EXPECT_EQ(s21_map.contains(3), true);
}

TEST(MapTest, Swap) {
  s21::map<int, std::string> s21_map1 = {{1, "one"}};
  s21::map<int, std::string> s21_map2 = {{2, "two"}};

  std::map<int, std::string> std_map1 = {{1, "one"}};
  std::map<int, std::string> std_map2 = {{2, "two"}};

  s21_map1.swap(s21_map2);
  std_map1.swap(std_map2);

  EXPECT_EQ(s21_map1.size(), std_map1.size());
  EXPECT_EQ(s21_map2.size(), std_map2.size());
  EXPECT_EQ(s21_map1.contains(2), true);
  EXPECT_EQ(s21_map2.contains(1), true);
}

TEST(MapTest, Merge) {
  s21::map<int, std::string> s21_map1 = {{1, "one"}};
  s21::map<int, std::string> s21_map2 = {{2, "two"}};

  std::map<int, std::string> std_map1 = {{1, "one"}};
  std::map<int, std::string> std_map2 = {{2, "two"}};

  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);

  EXPECT_EQ(s21_map1.size(), std_map1.size());
  EXPECT_EQ(s21_map2.size(), std_map2.size());
  EXPECT_EQ(s21_map1.contains(1), true);
  EXPECT_EQ(s21_map1.contains(2), true);
}

TEST(MapTest, Contains) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};

  EXPECT_EQ(s21_map.contains(1), std_map.count(1) > 0);
  EXPECT_EQ(s21_map.contains(2), std_map.count(2) > 0);
  EXPECT_EQ(s21_map.contains(3), std_map.count(3) > 0);
}

TEST(MapTest, Size) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());

  s21_map.insert({1, "one"});
  std_map.insert({1, "one"});

  EXPECT_EQ(s21_map.size(), std_map.size());

  s21_map.insert({2, "two"});
  std_map.insert({2, "two"});

  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapTest, Empty) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.empty(), std_map.empty());

  s21_map.insert({1, "one"});
  std_map.insert({1, "one"});

  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(MapTest, Clear) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};

  s21_map.clear();
  std_map.clear();

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(MapTest, Find) {
  s21::map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};

  auto s21_it = s21_map.find(1);
  auto std_it = std_map.find(1);

  EXPECT_EQ(s21_it->first, std_it->first);
  EXPECT_EQ(s21_it->second, std_it->second);

  s21_it = s21_map.find(3);
  std_it = std_map.find(3);

  EXPECT_EQ(s21_it == s21_map.end(), std_it == std_map.end());
}

TEST(MapTest, InsertMany) {
  s21::map<int, std::string> s21_map;
  auto results = s21_map.insert_many(
      std::make_pair(1, "one"), std::make_pair(2, "two"),
      std::make_pair(3, "three"), std::make_pair(2, "duplicate"));
  ASSERT_EQ(results.size(), 4);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);

  EXPECT_EQ(s21_map.size(), 3);
  EXPECT_EQ(s21_map.at(1), "one");
  EXPECT_EQ(s21_map.at(2), "two");
  EXPECT_EQ(s21_map.at(3), "three");
}

}  // namespace
