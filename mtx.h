#ifndef MTX_H
#define MTX_H
#include <iostream>
#include <cstddef>
class Matrix
{
 public:
  ~Matrix();
  Matrix(size_t m, size_t n);
  Matrix(const Matrix& rhs);
  void readMatrix(std::istream& input);
  void writeMatrix(std::ostream& output) const;
  int** t_;
  size_t m_, n_;
};
#endif
