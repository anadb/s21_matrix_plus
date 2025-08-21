#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <iostream>
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define EPSILON 1e-7
using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(double** matrix, int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  ~S21Matrix();
  bool EqMatrix(const S21Matrix& other);
  bool operator==(const S21Matrix& rhs);

  void SumMatrix(const S21Matrix& other);
  void operator+=(const S21Matrix& rhs);
  S21Matrix operator+(const S21Matrix& rhs) const;

  void SubMatrix(const S21Matrix& other);
  void operator-=(const S21Matrix& rhs);
  S21Matrix operator-(const S21Matrix& rhs) const;

  void MulNumber(const double num);
  void operator*=(const double num);
  S21Matrix operator*(const double num) const;

  void MulMatrix(const S21Matrix& other);
  void operator*=(const S21Matrix& rhs);
  S21Matrix operator*(const S21Matrix& rhs) const;
  S21Matrix Transpose();

  S21Matrix SubMatrix(int r, int c);
  void Determinant(S21Matrix& other, double* result);
  double Determinant();

  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double& operator()(int i, int j) const;

  void PrintMatrix();
};

#endif
