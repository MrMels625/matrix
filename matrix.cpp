#include <iostream>
#include "matrix.h"

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
  catch (const std::bad_alloc &e) {
    destroyMatrix(matrix, created);
    throw;
  }
  return matrix;
}

void readMatrix(std::istream& input, int** matrix, size_t m, size_t n)
{
  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      input >> matrix[i][j];
    }
  }
}

void writeMatrix(std::ostream& output, const int* const* matrix, size_t m, size_t n)
{
  for (size_t i = 0; i < m; i++)
  {
    output << matrix[i][0];
    for (size_t j = 1; j < n; j++)
    {
      output << " " << matrix[i][j];
    }
    output << "\n";
  }
}

void copyMatrix(int** matrix, int** newMatrix, size_t m, size_t n) 
{
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      newMatrix[i][j] = matrix[i][j];
    }
  }
}

