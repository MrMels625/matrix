#include <iostream>
#include "matrix.h"
#include "mtx.h"

int main()
{
  int m = 0, n = 0;
  std::cin >> m >> n;
  if (!std::cin || m <= 0 || n <= 0)
  {
    std::cerr << "ERROR: Input was incorrect!\n";
    return 1;
  }
  try
  {
    Matrix mtx1(m, n);
    Matrix mtx(mtx1);
    std::cout << "Number of rows: " << mtx.getRows() << "\n";
    std::cout << "Number of columns: " << mtx.getColumns() << "\n";

    std::cout << "Enter some numbers to fill in the matrix with current size: ";
    mtx.read(std::cin);
    std::cout << "\n";
    std::cout << "Matrix filled in with entered numbers:\n";
    mtx.write(std::cout);

    mtx.fillIn(3);
    std::cout << "Matrix filled in with 3:\n";
    mtx.write(std::cout);

    mtx.changeSize(3, 2);
    mtx.fillIn(4);
    std::cout << "Matrix size changed to 3x2 and filled in with 4:\n";
    mtx.write(std::cout);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "ERROR: Out of memory!\n";
    return 1;
  }
}
