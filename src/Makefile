CXX = g++
CFLAGS = -Wall -Wextra -Werror
LIB = s21_matrix_oop.a
SRCS = $(filter-out test.cpp, $(wildcard *.cpp))
LIB_OBJ = $(SRCS:.cpp=.o)

all: $(LIB) test

$(LIB): $(LIB_OBJ)
	$(AR) rcs lib$(LIB) $(LIB_OBJ)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

test: $(LIB)
	$(CXX) $(CFLAGS) test.cpp -L. -l$(basename $(LIB)) -lgtest -o test

clean:
	$(RM) *.o *.a *.out test
