#pragma once

class Matrix {
  int rows_;
  int cols_;
  double **m_;

  class Rows;

public:
  Matrix(int r, int c); // constructor
  ~Matrix();            // destructor
  Matrix();
  Matrix(const Matrix &m);            // constructor copy
  Matrix &operator=(const Matrix &m); // operator =

  Rows operator[](int i);
  const Rows operator[](int i) const;
};
