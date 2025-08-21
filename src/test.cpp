#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

TEST(Function, EqMatrix) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);
  S21Matrix matr2(2, 2);
  ASSERT_EQ(false, matr1.EqMatrix(matr2));
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, EqMatrixOperator) {
  S21Matrix matr1(2, 2);
  S21Matrix matr2(2, 2);
  ASSERT_EQ(true, matr1 == matr2);
}

TEST(Function, SumMatrix) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);

  mat[0][0] = 5;
  mat[0][1] = 6;
  mat[1][0] = 7;
  mat[1][1] = 8;
  S21Matrix matr2(mat, 2, 2);

  // matr1.SumMatrix(matr2);
  matr1 += matr2;

  mat[0][0] = 6;
  mat[0][1] = 8;
  mat[1][0] = 10;
  mat[1][1] = 12;
  S21Matrix matr3(mat, 2, 2);

  ASSERT_EQ(true, matr1 == matr3);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, OperatorPlus) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);

  mat[0][0] = 5;
  mat[0][1] = 6;
  mat[1][0] = 7;
  mat[1][1] = 8;
  S21Matrix matr2(mat, 2, 2);

  mat[0][0] = 6;
  mat[0][1] = 8;
  mat[1][0] = 10;
  mat[1][1] = 12;
  S21Matrix matr3(mat, 2, 2);

  S21Matrix result = matr1 + matr2;

  ASSERT_EQ(true, result == matr3);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, SubMatrix) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);

  mat[0][0] = 5;
  mat[0][1] = 6;
  mat[1][0] = 7;
  mat[1][1] = 8;
  S21Matrix matr2(mat, 2, 2);

  // matr2.SubMatrix(matr1);
  matr2 -= matr1;

  mat[0][0] = 4;
  mat[0][1] = 4;
  mat[1][0] = 4;
  mat[1][1] = 4;
  S21Matrix matr3(mat, 2, 2);

  ASSERT_EQ(true, matr2 == matr3);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, OperatorMinus) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);

  mat[0][0] = 5;
  mat[0][1] = 6;
  mat[1][0] = 7;
  mat[1][1] = 8;
  S21Matrix matr2(mat, 2, 2);

  mat[0][0] = 4;
  mat[0][1] = 4;
  mat[1][0] = 4;
  mat[1][1] = 4;
  S21Matrix matr3(mat, 2, 2);

  S21Matrix result = matr2 - matr1;

  ASSERT_EQ(true, result == matr3);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, MulNumber) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);

  mat[0][0] = 2;
  mat[0][1] = 4;
  mat[1][0] = 6;
  mat[1][1] = 8;
  S21Matrix matr2(mat, 2, 2);

  S21Matrix result = matr1 * 2.0;
  matr1 *= 2.0;
  ASSERT_EQ(true, matr1 == matr2);
  ASSERT_EQ(true, result == matr2);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

TEST(Function, MulMatrix) {
  double **mat1 = new double *[3];
  for (int i = 0; i < 3; i++) mat1[i] = new double[2];
  mat1[0][0] = 1;
  mat1[0][1] = 4;
  mat1[1][0] = 2;
  mat1[1][1] = 5;
  mat1[2][0] = 3;
  mat1[2][1] = 6;
  S21Matrix matr1(mat1, 3, 2);

  double **mat2 = new double *[2];
  for (int i = 0; i < 2; i++) mat2[i] = new double[3];
  mat2[0][0] = 1;
  mat2[0][1] = -1;
  mat2[0][2] = 1;
  mat2[1][0] = 2;
  mat2[1][1] = 3;
  mat2[1][2] = 4;
  S21Matrix matr2(mat2, 2, 3);

  // matr1.MulMatrix(matr2);

  double **mat3 = new double *[3];
  for (int i = 0; i < 3; i++) mat3[i] = new double[3];
  mat3[0][0] = 9;
  mat3[0][1] = 11;
  mat3[0][2] = 17;
  mat3[1][0] = 12;
  mat3[1][1] = 13;
  mat3[1][2] = 22;
  mat3[2][0] = 15;
  mat3[2][1] = 15;
  mat3[2][2] = 27;

  S21Matrix matr3(mat3, 3, 3);
  ASSERT_EQ(true, matr1 * matr2 == matr3);

  matr1 *= matr2;
  ASSERT_EQ(true, matr1 == matr3);

  for (int i = 0; i < 3; i++) delete[] mat1[i];
  delete[] mat1;
  for (int i = 0; i < 2; i++) delete[] mat2[i];
  delete[] mat2;
  for (int i = 0; i < 3; i++) delete[] mat3[i];
  delete[] mat3;
}

TEST(Function, Transpose) {
  double **mat1 = new double *[3];
  for (int i = 0; i < 3; i++) mat1[i] = new double[2];
  mat1[0][0] = 1;
  mat1[0][1] = 4;
  mat1[1][0] = 2;
  mat1[1][1] = 5;
  mat1[2][0] = 3;
  mat1[2][1] = 6;
  S21Matrix matr1(mat1, 3, 2);

  double **mat2 = new double *[2];
  for (int i = 0; i < 2; i++) mat2[i] = new double[3];
  mat2[0][0] = 1;
  mat2[0][1] = 2;
  mat2[0][2] = 3;
  mat2[1][0] = 4;
  mat2[1][1] = 5;
  mat2[1][2] = 6;
  S21Matrix matr2(mat2, 2, 3);

  S21Matrix matr3 = matr1.Transpose();

  ASSERT_EQ(true, matr2 == matr3);
  for (int i = 0; i < 3; i++) delete[] mat1[i];
  delete[] mat1;
  for (int i = 0; i < 2; i++) delete[] mat2[i];
  delete[] mat2;
}

TEST(Function, Determinant) {
  double **mat1 = new double *[3];
  for (int i = 0; i < 3; i++) mat1[i] = new double[3];
  mat1[0][0] = 1;
  mat1[0][1] = 2;
  mat1[0][2] = 3;
  mat1[1][0] = 0;
  mat1[1][1] = 4;
  mat1[1][2] = 2;
  mat1[2][0] = 5;
  mat1[2][1] = 2;
  mat1[2][2] = 1;

  S21Matrix matr1(mat1, 3, 3);
  double det = matr1.Determinant();
  ASSERT_NEAR(-40, det, EPSILON);
  for (int i = 0; i < 3; i++) delete[] mat1[i];
  delete[] mat1;
}

TEST(Function, CalcComplements) {
  double **mat1 = new double *[4];
  for (int i = 0; i < 4; i++) mat1[i] = new double[4];
  mat1[0][0] = 1.32;
  mat1[0][1] = 0.25;
  mat1[0][2] = 3.40;
  mat1[0][3] = 3.65;
  mat1[1][0] = 0.05;
  mat1[1][1] = -4.1;
  mat1[1][2] = 2.07;
  mat1[1][3] = 0.43;
  mat1[2][0] = 5.56;
  mat1[2][1] = 2.12;
  mat1[2][2] = 0.19;
  mat1[2][3] = 33.1;
  mat1[3][0] = 2.65;
  mat1[3][1] = 8.54;
  mat1[3][2] = -6.4;
  mat1[3][3] = 7.44;

  S21Matrix matr1(mat1, 4, 4);
  S21Matrix matr2 = matr1.CalcComplements();

  mat1[0][0] = -328.386234;
  mat1[0][1] = -91.086657;
  mat1[0][2] = -185.372628;
  mat1[0][3] = 62.058972;
  mat1[1][0] = -905.33179;
  mat1[1][1] = 307.360617;
  mat1[1][2] = 187.917374;
  mat1[1][3] = 131.309243;
  mat1[2][0] = 151.98931;
  mat1[2][1] = -5.381121;
  mat1[2][2] = -3.704909;
  mat1[2][3] = -51.146279;
  mat1[3][0] = -462.761255;
  mat1[3][1] = 50.862411;
  mat1[3][2] = 96.564262;
  mat1[3][3] = 73.920757;

  S21Matrix matr3(mat1, 4, 4);

  ASSERT_EQ(true, matr2 == matr3);
  for (int i = 0; i < 4; i++) delete[] mat1[i];
  delete[] mat1;
}

TEST(Function, Inverse) {
  double **mat1 = new double *[3];
  for (int i = 0; i < 3; i++) mat1[i] = new double[3];
  mat1[0][0] = 2;
  mat1[0][1] = 5;
  mat1[0][2] = 7;
  mat1[1][0] = 6;
  mat1[1][1] = 3;
  mat1[1][2] = 4;
  mat1[2][0] = 5;
  mat1[2][1] = -2;
  mat1[2][2] = -3;

  S21Matrix matr1(mat1, 3, 3);

  mat1[0][0] = 1;
  mat1[0][1] = -1;
  mat1[0][2] = 1;
  mat1[1][0] = -38;
  mat1[1][1] = 41;
  mat1[1][2] = -34;
  mat1[2][0] = 27;
  mat1[2][1] = -29;
  mat1[2][2] = 24;

  S21Matrix matr2(mat1, 3, 3);

  ASSERT_EQ(true, matr1.InverseMatrix() == matr2);
  for (int i = 0; i < 3; i++) delete[] mat1[i];
  delete[] mat1;
}

TEST(Function, Indexation) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) mat[i] = new double[2];
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  mat[1][1] = 4;
  S21Matrix matr1(mat, 2, 2);
  ASSERT_NEAR(2, matr1(0, 1), EPSILON);
  for (int i = 0; i < 2; i++) delete[] mat[i];
  delete[] mat;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
