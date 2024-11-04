#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

int** createMatrix(size_t m, size_t n);
void destroyMatrix(int** matrix, size_t m);
void readMatrix(std::istream& input, int** matrix, size_t m, size_t n);
void writeMatrix(std::ostream& output, const int* const* matrix, size_t m, size_t n);
void copyMatrix(int** matrix, int** newMatrix, size_t m, size_t n);
size_t getMatrixRows(size_t m);
size_t getMatrixColumns(size_t n);

#endif
