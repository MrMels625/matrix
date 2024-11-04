#include "mtx.h"
#include "matrix.h"

Matrix::~Matrix()
{
  ::destroyMatrix(t_, m_);
}

Matrix::Matrix(size_t m, size_t n):
  t_(::createMatrix(m, n)), m_(m), n_(n)
{}

Matrix::Matrix(const Matrix& rhs):
  t_(::createMatrix(rhs.m_, rhs.n_)), m_(rhs.m_), n_(rhs.n_)
{
  ::copyMatrix(rhs.t_, t_, m_, n_);
}

void Matrix::read(std::istream& input)
{
  ::readMatrix(input, t_, m_, n_);
}

void Matrix::write(std::ostream& output) const
{
  ::writeMatrix(output, t_, m_, n_);
}

size_t Matrix::getRows() const
{
  return m_;
}

size_t Matrix::getColumns() const
{
  return n_;
}

void Matrix::fillIn(size_t num)
{
  for (size_t i = 0; i < m_; ++i)
  {
    for (size_t j = 0; j < n_; ++j)
    {
      t_[i][j] = num;
    }
  }
}

void Matrix::changeSize(size_t mNew, size_t nNew)
{
  ::destroyMatrix(t_, m_);
  m_ = mNew;
  n_ = nNew;
  t_ = ::createMatrix(m_, n_);
}

