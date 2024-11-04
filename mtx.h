#ifndef MTX_H
#define MTX_H

#include <iostream>
#include <cstddef>

class Matrix
{
 public:
  int** t_;
  size_t m_, n_;
  ~Matrix();
  Matrix(size_t m, size_t n);
  Matrix(const Matrix& rhs);
  void read(std::istream& input);
  void write(std::ostream& output) const;
  size_t getRows() const;
  size_t getColumns() const;
  void fillIn();
};

#endif

