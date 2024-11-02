#include <iostream>
#include "matrix.h"
#include "mtx.h"

int main()
{
  size_t m = 0, n = 0;
  std::cin >> m >> n;
  if (!std::cin)
  {
    std::cerr << "ERROR: Input was incorrect!\n";
    return 1;
  }
  try
  {
    Matrix mtx(m, n);
    Matrix mtx2(mtx);
    mtx2.readMatrix(std::cin);
    mtx2.writeMatrix(std::cout);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "ERROR: Out of memory!\n";
    return 1;
  }
}
