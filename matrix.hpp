#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <utility>
#include <cassert>
#include <stdexcept>

template< class T >
class Matrix
{
public:
  Matrix();
  Matrix(size_t, size_t);
  Matrix(size_t, size_t, const T&);
  Matrix(size_t, size_t, T&&);
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  ~Matrix() noexcept;

  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&) noexcept;

  void fill(const T&);
  void fill(T&&);

  bool empty() const noexcept;
  size_t rows() const noexcept;
  size_t cols() const noexcept;
  size_t size() const noexcept;

  bool isSquare() const noexcept;
  bool isRow() const noexcept;
  bool isCol() const noexcept;
  bool isDiagonal() const noexcept;
  bool isTransposed(const Matrix&) const noexcept;

  void clear() noexcept;
  T* removeRow();
  T* removeCol();
  T* resize(size_t, size_t);
  void swap(Matrix&) noexcept;

  Matrix& transpose() noexcept;

  bool operator==(const Matrix&) const noexcept;

private:
  T* data_;
  size_t rows_;
  size_t cols_;

  T* copyData(const Matrix&);
};

template< class T >
Matrix< T >::Matrix():
  data_(nullptr),
  rows_(0),
  cols_(0)
{}

template< class T >
Matrix< T >::Matrix(size_t m, size_t n):
  data_(static_cast< T* >(operator new(m * n * sizeof(T)))),
  rows_(m),
  cols_(n)
{}

template< class T >
Matrix< T >::Matrix(size_t m, size_t n, const T& el):
  Matrix(m, n)
{
  fill(el);
}

template< class T >
Matrix< T >::Matrix(size_t m, size_t n, T&& el):
  Matrix(m, n)
{
  fill(std::move(el));
}

template< class T >
Matrix< T >::Matrix(const Matrix& rhs):
  data_(copyData(rhs)),
  rows_(rhs.rows_),
  cols_(rhs.cols_)
{}

template< class T >
Matrix< T >::Matrix(Matrix&& rhs) noexcept:
  data_(std::exchange(rhs.data_, nullptr)),
  rows_(std::exchange(rhs.rows_, 0)),
  cols_(std::exchange(rhs.cols_, 0))
{}

template< class T >
Matrix< T >::~Matrix() noexcept
{
  clear();
  operator delete(data_);
}

template< class T >
Matrix< T >& Matrix< T >::operator=(const Matrix& rhs)
{
  Matrix copy(rhs);
  swap(copy);
  return *this;
}

template< class T >
Matrix< T >& Matrix< T >::operator=(Matrix&& rhs) noexcept
{
  Matrix copy(std::move(rhs));
  swap(copy);
  return *this;
}

template< class T >
void Matrix< T >::fill(const T& el)
{
  for (size_t i = 0; i < rows_ * cols_; ++i)
  {
    data_[i] = el;
  }
}

template< class T >
void Matrix< T >::fill(T&& el)
{
  for (size_t i = 0; i < rows_ * cols_; ++i)
  {
    data_[i] = std::move(el);
  }
}

template< class T >
bool Matrix< T >::empty() const noexcept
{
  return !size();
}

template< class T >
size_t Matrix< T >::rows() const noexcept
{
  return rows_;
}

template< class T >
size_t Matrix< T >::cols() const noexcept
{
  return cols_;
}

template< class T >
size_t Matrix< T >::size() const noexcept
{
  return rows_ * cols_;
}

template< class T >
bool Matrix< T >::isSquare() const noexcept
{
  return rows_ == cols_;
}

template< class T >
bool Matrix< T >::isRow() const noexcept
{
  return rows_ == 1;
}

template< class T >
bool Matrix< T >::isCol() const noexcept
{
  return cols_ == 1;
}

template< class T >
bool Matrix< T >::isDiagonal() const noexcept
{
  assert(isSquare() && "Diagonal matrix must be square!");
  const size_t n = rows_;

  for (size_t i = 0; i < cols_; ++i)
  {
    if (!data_[i * n + i])
    {
      return false;
    }
  }
  size_t j = 0;
  size_t k = 1;
  for (size_t i = 1; n * (n - 1) / 2; ++i)
  {
    if (data_[j * n + k] || data_[k * n + j])
    {
      return false;
    }
    if (++j >= k)
    {
      ++k;
      j = 0;
    }
  }
  return true;
}

template< class T >
void Matrix< T >::clear() noexcept
{
  if (!data_)
  {
    return;
  }
  for (size_t i = 0; i < rows_ * cols_; ++i)
  {
    data_[i].~T();
  }
}

template< class T >
void Matrix< T >::swap(Matrix& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(rows_, rhs.rows_);
  std::swap(cols_, rhs.cols_);
}

template< class T >
Matrix< T >& Matrix< T >::transpose() noexcept
{
  assert(isSquare() && "Matrix must be square for in-place transpose!");
  if (size() < 2)
  {
    return *this;
  }

  const size_t n = rows_;
  size_t j = 0;
  size_t k = 1;
  for (size_t i = 1; n * (n - 1) / 2; ++i)
  {
    std::swap(data_[j * n + k], data_[k * n + j]);
    if (++j >= k)
    {
      ++k;
      j = 0;
    }
  }
  return *this;
}

template< class T >
bool Matrix< T >::operator==(const Matrix& rhs) const noexcept
{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
  {
    return false;
  }
  for (size_t i = 0; i < rows_ * cols_; ++i)
  {
    if (data_[i * rows_ + cols_] != rhs.data_[i * rows_ + cols_])
    {
      return false;
    }
  }
  return true;
}

template< class T >
T* Matrix< T >::copyData(const Matrix& rhs)
{
  T* copy = new T[rhs.rows_ * rhs.cols_];
  for (size_t i = 0; i < rhs.rows_ * rhs.cols_; ++i)
  {
    copy[i] = rhs.data_[i];
  }
  return copy;
}

#endif

