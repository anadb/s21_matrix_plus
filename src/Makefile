CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest -lgtest_main -pthread
LCOV_IGNORE = --ignore-errors deprecated,inconsistent,mismatch

TEST_SRCS = test_array.cpp test_queue.cpp test_multiset.cpp test_set.cpp test_map.cpp test_list.cpp test_stack.cpp test_vector.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXEC = run_tests

HEADERS = include/s21_array.h include/s21_queue.h include/s21_multiset.h include/s21_set.h \
          include/s21_map.h include/s21_list.h include/s21_stack.h include/s21_vector.h \
          include/s21_tree.h

GCOV_FILES = $(wildcard *.gcda *.gcno *.gcov)
COVERAGE_DIR = coverage
COVERAGE_INFO = $(COVERAGE_DIR)/coverage.info
COVERAGE_REPORT = $(COVERAGE_DIR)/index.html

all: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

format:
	cp ../materials/linters/.clang-format ./
	cp ../materials/linters/.clang-format include/
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} +

test: $(TEST_EXEC)
	./$(TEST_EXEC)

gcov_report: test
	@mkdir -p $(COVERAGE_DIR)
	lcov --capture --directory . --output-file $(COVERAGE_INFO) --branch-coverage $(LCOV_IGNORE)
	lcov --remove $(COVERAGE_INFO) '/usr/*' --output-file $(COVERAGE_INFO)
	genhtml $(COVERAGE_INFO) --output-directory $(COVERAGE_DIR) --branch-coverage --ignore-errors inconsistent
	@echo "Coverage report generated at $(COVERAGE_DIR)/index.html"

clean:
	rm -rf $(TEST_OBJS) $(TEST_EXEC) $(GCOV_FILES) $(COVERAGE_DIR) .clang-format include/.clang-format

rebuild: clean all

.PHONY: all test gcov_report clean rebuild
