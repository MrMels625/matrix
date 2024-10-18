#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
int** createMatrix(size_t m, size_t n);
void destroyMatrix(int** matrix, size_t m);
void readMatrix(int** matrix, size_t m, size_t n);
void writeMatrix(const int* const* matrix, size_t m, size_t n);
#endif
