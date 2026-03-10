#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
  Matrix M(3, 4);

  cout << M;
  M[1][1] = 2;
  cout << endl;
  cout << M;
  return 0;
}
