#include "matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() : rows(0), cols(0), m(nullptr) {}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
  m = new double *[r];
  for (int i = 0; i < rows; i++) {
    m[i] = new double[c];
    for (int j = 0; j < cols; j++)
      m[i][j] = 0;
  }
}

Matrix::~Matrix() {
  if (!m)
    return;
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

Matrix::Row::Row(int row, int cols, double **p) : cols(cols), r(p[row]) {}

double &Matrix::Row::operator[](int j) { return r[j]; }

const double &Matrix::Row::operator[](int j) const { return r[j]; }

Matrix::Row Matrix::operator[](int i) { return Row(i, cols, m); }

const Matrix::Row Matrix::operator[](int i) const { return Row(i, cols, m); }

ostream &operator<<(ostream &s, const Matrix &M) {
  for (int i = 0; i < M.rows; i++) {
    for (int j = 0; j < M.cols; j++)
      s << M.m[i][j] << " ";
    s << endl;
  }
  return s;
}
