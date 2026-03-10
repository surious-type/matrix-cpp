#pragma once
#include <iostream>

class Matrix {
  int rows_;
  int cols_;
  double **m_;

  class Row {
    int cols;
    double *&r;

  public:
    Row(int row, int cols, double **p) : r(p[row]), cols(cols) {}
    double &operator[](int j) { return r[j]; }
    const double &operator[](int j) const : r[j]
  };

public:
  Matrix(int r, int c); // constructor
  ~Matrix();            // destructor
  Matrix();
  Matrix(const Matrix &m);            // constructor copy
  Matrix &operator=(const Matrix &m); // operator =

  Row operator[](int i) {};
  const Row operator[](int i) const {};

  friend std::ostream &operator<<(std::ostream &s, const Matrix &M) {};
