#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
  Matrix M;

  cout << M;
  M[1][1] = 0;
  cout << endl;
  cout << M;
  return 0;
}
