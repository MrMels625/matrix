#include <iostream>
#include "matrix.hpp"

int main()
{
  size_t M = 0, N = 0;
  std::cin >> M >> N;

  int** matrix = nullptr;
  try
  {
    matrix = createMatrix(M, N);
  } catch (const std::bad_alloc & e) {
    std::cerr << "ERROR: Out of memory!\n";
    destroyMatrix(matrix, M);
    return 1;
  }
  readMatrix(matrix, M, N);
  writeMatrix(matrix, M, N);
  destroyMatrix(matrix, M);
}
