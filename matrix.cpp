#include "matrix.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Matrix::Exception::Exception(const char *msg) : msg(msg) {}

const char *Matrix::Exception::what() const { return msg; }

Matrix::Matrix() : rows(0), cols(0), m(nullptr) {}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
  if (r <= 0)
    throw Exception("rows must be > 0");

  if (c <= 0)
    throw Exception("cols must be > 0")

        m = new double *[r];
  for (int i = 0; i < rows; i++) {
    m[i] = new double[c];
    for (int j = 0; j < cols; j++)
      m[i][j] = 0;
  }
}

Matrix::~Matrix() {
  if (!m) {
    return;
  }
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

Matrix::Row::Row(int row, int cols, double **p) : cols(cols), r(p[row]) {}

double &Matrix::Row::operator[](int j) {
  if (j < 0 || j >= cols)
    throw Exception("cols index output of range");
  return r[j];
}

const double &Matrix::Row::operator[](int j) const {
  if (j < 0 || j >= cols)
    throw Exception("cols index output of range");
  return r[j];
}

Matrix::Row Matrix::operator[](int i) {
  if (i < 0 || i >= rows)
    throw Exception("rows index output of range");
  return Row(i, cols, m);
}

const Matrix::Row Matrix::operator[](int i) const {
  if (i < 0 || i >= rows)
    throw Exception("rows index output of range");
  return Row(i, cols, m);
}

ostream &operator<<(ostream &s, const Matrix &M) {
  for (int i = 0; i < M.rows; i++) {
    for (int j = 0; j < M.cols; j++)
      s << M.m[i][j] << " ";
    s << endl;
  }
  return s;
}

Matrix::Matrix(double value) : rows(1), cols(1) {
  m = new double *[1];
  m[0] = new double[1];
  m[0][0] = value;
}

Matrix::Matrix(double *vals, int c) : rows(1), cols(c) {
  m = new double *[1];
  m[0] = new double[cols];

  for (int j = 0; j < cols; j++) {
    m[0][j] = vals[j];
  }
} // 1 x m - matrix row

Matrix::Matrix(int n, double *vals) : rows(n), cols(1) {
  m = new double *[rows];

  for (int i = 0; i < n; i++) {
    m[i] = new double[1];
    m[i][0] = vals[i];
  }
} // n x 1 - matrix col

Matrix::Matrix(const char *text) : rows(0), cols(0) {
  const char *p = text;

  while (*p) {
    if (*p == '{' && *(p + 1) != '{')
      rows++;
    p++;
  }

  p = text;
  p += 2;
  while (*p && *p != '}') {
    if ((*p >= '0' && *p <= '9') || *p == '-' || *p == '.') {
      char *end;
      strtod(p, &end);
      p = end;
      cols++;
    } else {
      p++;
    }
  };

  m = new double *[rows];
  for (int i = 0; i < rows; i++) {
    m[i] = new double[cols];
  }
  p = text;
  int k = 0;

  while (*p) {

    if ((*p >= '0' && *p <= '9') || *p == '-' || *p == '.') {

      char *end;
      double val = strtod(p, &end);

      int i = k / cols;
      int j = k % cols;

      m[i][j] = val;

      k++;
      p = end;
      continue;
    }

    p++;
  }
} // matrix from chars

Matrix::Matrix(const Matrix &other) : rows(other.rows), cols(other.cols) {
  m = new double *[rows];

  for (int i = 0; i < rows; i++) {
    m[i] = new double[cols];
    for (int j = 0; j < cols; j++) {
      m[i][j] = other.m[i][j];
    }
  }
} // constructor copy
Matrix &Matrix::operator=(const Matrix &other) {
  if (this == &other) {
    return *this;
  }

  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;

  rows = other.rows;
  cols = other.cols;

  m = new double *[rows];

  for (int i = 0; i < rows; i++) {
    m[i] = new double[cols];
    for (int j = 0; j < cols; j++) {
      m[i][j] = other.m[i][j];
    }
  }

  return *this;
} // operator =
Matrix Matrix::identity(int n) {
  Matrix I(n, n);

  for (int i = 0; i < n; i++) {
    I[i][i] = 1;
  }

  return I;
} // единичная матрица
Matrix Matrix::diagonal(double *vals, int n) {
  Matrix D(n, n);

  for (int i = 0; i < n; i++) {
    D[i][i] = vals[i];
  }

  return D;
} // diagonal matrix
Matrix Matrix::operator*(double k) const {
  Matrix C(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      C.m[i][j] = m[i][j] * k;
    }
  }
  return C;
}
Matrix &Matrix::operator*=(double k) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m[i][j] = m[i][j] * k;
    }
  }

  return *this;
}
