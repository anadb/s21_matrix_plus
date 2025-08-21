#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 2;
  cols_ = 2;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument("S21Matrix: rows=" + std::to_string(rows_) +
                                " and columns=" + std::to_string(cols_) +
                                " must be greater than zero.");
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(double** matrix, int rows, int cols)
    : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument("S21Matrix: rows=" + std::to_string(rows_) +
                                " and columns=" + std::to_string(cols_) +
                                " must be greater than zero.");
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix[i][j];
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool isEqual = true;
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("S21Matrix: dimensions must be the same");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      if (ABS(matrix_[i][j] - other.matrix_[i][j]) > EPSILON) {
        isEqual = false;
        break;
      }
    if (!isEqual) break;
  }
  return isEqual;
}

bool S21Matrix::operator==(const S21Matrix& rhs) { return EqMatrix(rhs); }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("S21Matrix: dimensions must be the same");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::operator+=(const S21Matrix& rhs) { SumMatrix(rhs); }

S21Matrix S21Matrix::operator+(const S21Matrix& rhs) const {
  S21Matrix result = *this;
  result += rhs;
  return result;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("S21Matrix: dimensions must be the same");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::operator-=(const S21Matrix& rhs) { SubMatrix(rhs); }

S21Matrix S21Matrix::operator-(const S21Matrix& rhs) const {
  S21Matrix result = *this;
  result -= rhs;
  return result;
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  result *= num;
  return result;
}

void S21Matrix::operator*=(const double num) { MulNumber(num); }

S21Matrix S21Matrix::operator*(const S21Matrix& rhs) const {
  S21Matrix result = *this;
  result *= rhs;
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "S21Matrix: matrix1 number of cols must be equal matrix2 number of "
        "rows");

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::operator*=(const S21Matrix& rhs) { MulMatrix(rhs); }

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) transposed.matrix_[j][i] = matrix_[i][j];
  return transposed;
}

S21Matrix S21Matrix::SubMatrix(int r, int c) {
  S21Matrix SubMatrix_(rows_ - 1, cols_ - 1);
  for (int i = 0, p = 0; i < rows_; i++) {
    if (i != r) {
      for (int j = 0, q = 0; j < cols_; j++) {
        if (j != c) {
          SubMatrix_.matrix_[p][q] = matrix_[i][j];
          q++;
        }
      }
      p++;
    }
  }

  return SubMatrix_;
}

void S21Matrix::Determinant(S21Matrix& other, double* result) {
  if (cols_ != rows_)
    throw std::invalid_argument("S21Matrix: matrix is not square");
  if (other.rows_ == 1)
    *result = 0;
  else if (other.rows_ == 2)
    *result = other.matrix_[0][0] * other.matrix_[1][1] -
              other.matrix_[1][0] * other.matrix_[0][1];
  else {
    *result = 0.0;
    int sign = 1;
    S21Matrix SubMatrix_(other.rows_ - 1, other.cols_ - 1);
    for (int i = 0; i < cols_; i++) {
      double det = 0.0;
      SubMatrix_ = other.SubMatrix(0, i);
      Determinant(SubMatrix_, &det);
      *result += sign * matrix_[0][i] * det;
      sign = -sign;
    }
  }
}

double S21Matrix::Determinant() {
  double det = 0.0;
  Determinant(*this, &det);
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_)
    throw std::invalid_argument("S21Matrix: matrix is not square");
  S21Matrix result(rows_, cols_);
  S21Matrix SubMatrix_(rows_ - 1, cols_ - 1);
  double det;
  int sign;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) {
      SubMatrix_ = this->SubMatrix(i, j);
      det = SubMatrix_.Determinant();
      if ((i + j) % 2 == 0)
        sign = 1;
      else
        sign = -1;
      result.matrix_[i][j] = sign * det;
    }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0)
    throw std::invalid_argument(
        "S21Matrix: det = 0; inverse matrix is undefined");
  S21Matrix Inverse = this->CalcComplements().Transpose();
  Inverse.MulNumber(1.0 / det);
  return Inverse;
}

double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::invalid_argument("S21Matrix: index is out of bounds");
  return matrix_[i][j];
}

void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) cout << matrix_[i][j] << ' ';
    cout << endl;
  }
}
