#include <iostream>
#include "matrix.hpp"

void destroyMatrix(int** matrix, size_t m)
{
  for (size_t i = 0; i < m; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** createMatrix(size_t m, size_t n)
{
  int** matrix = new int* [m];
  size_t created = 0;
  try
  {
    for (; created < m; created++)
    {
      matrix[created] = new int[n];
    }
  }
  catch (const std::bad_alloc & e) {
    destroyMatrix(matrix, created);
    throw;
  }
  return matrix;
}

void readMatrix(int** matrix, size_t m, size_t n)
{
  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      std::cin >> matrix[i][j];
    }
  }
}

void writeMatrix(const int* const* matrix, size_t m, size_t n)
{
  for (size_t i = 0; i < m; i++)
  {
    std::cout << matrix[i][0];
    for (size_t j = 1; j < n; j++)
    {
      std::cout << " " << matrix[i][j];
    }
    std::cout << "\n";
  }
}
