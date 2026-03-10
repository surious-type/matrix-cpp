#include <iostream>

// Пример реализации присваивания элементу матрицы NxN, N>0

using namespace std;

class Matrix {
  int rows;
  int cols;
  double **m;

public:
  Matrix(int r, int c) : rows(r), cols(c) {
    m = new double *[r];
    for (int i = 0; i < rows; i++) {
      m[i] = new double[c];
      for (int j = 0; j < cols; j++)
        m[i][j] = 0;
    }
  }

  ~Matrix() {
    if (!m)
      return;
    for (int i = 0; i < rows; i++) {
      delete[] m[i];
    }
    delete[] m;
  }

  class Row {
    int cols;
    double *&r;

  public:
    Row(int row, int cols, double **p) : r(p[row]) { this->cols = cols; }
    double &operator[](int j) { return r[j]; }
  };

  Row operator[](int i) { return Row(i, cols, m); }

  friend ostream &operator<<(ostream &s, const Matrix &M) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++)
        cout << M.m[i][j] << " ";
      cout << endl;
    }
    return s;
  }
};
