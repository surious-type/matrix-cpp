#pragma once
#include <iostream>

class Matrix {
  int rows;
  int cols;
  double **m;

public:
  class Row {
    int cols;
    double *&r;

  public:
    Row(int row, int cols, double **p);
    double &operator[](int j);
    const double &operator[](int j) const;
  };

  Matrix();
  Matrix(int r, int c);               // constructor
  ~Matrix();                          // destructor
  Matrix(const Matrix &m);            // constructor copy
  Matrix &operator=(const Matrix &m); // operator =

  Row operator[](int i);
  const Row operator[](int i) const;

  friend std::ostream &operator<<(std::ostream &s, const Matrix &M);
};
