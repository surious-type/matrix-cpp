#pragma once
#include <iostream>

class Matrix {
  int rows;
  int cols;
  double **m;

public:
  class Exception {
    const char *msg;

  public:
    Exception(const chat *msg);
    const char *what() const;
  };

  class Row {
    int cols;
    double *&r;

  public:
    Row(int row, int cols, double **p);
    double &operator[](int j);
    const double &operator[](int j) const;
  };

  Matrix();
  Matrix(int r, int c);                   // constructor
  ~Matrix();                              // destructor
  Matrix(double size);                    // 1 x 1
  Matrix(double *vals, int m);            // 1 x m - matrix row
  Matrix(int n, double *);                // n x 1 - matrix col
  Matrix(const char *);                   // matrix from chars
  Matrix(const Matrix &other);            // constructor copy
  Matrix &operator=(const Matrix &other); // operator =

  Row operator[](int i);
  const Row operator[](int i) const;

  friend std::ostream &operator<<(std::ostream &s, const Matrix &M);

  static Matrix identity(int n);               // единичная матрица
  static Matrix diagonal(double *vals, int n); // diagonal matrix
  Matrix operator*(double k) const;
  Matrix &operator*=(double k);
};
