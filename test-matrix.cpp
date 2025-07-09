#include <boost/test/unit_test.hpp>
#include "matrix.hpp"

BOOST_AUTO_TEST_CASE(constructors)
{
  Matrix< int > mtx1;
  BOOST_TEST(mtx1.empty());

  Matrix< int > mtx2(2, 2);
  BOOST_TEST(!mtx2.empty());

  int num = 1;
  Matrix< int > mtx3(2, 2, num);
  BOOST_TEST(mtx3.size() == 4);
   
  Matrix< int > mtx4(2, 2, 1);
  BOOST_TEST(mtx4.size() == 4);

  Matrix< int > mtx5(mtx4);
  BOOST_TEST(mtx5.size() == mtx4.size());

  Matrix< int > mtx6(std::move(mtx4));
  BOOST_TEST(mtx6.size() == 4);
  BOOST_TEST(mtx4.empty());
}

BOOST_AUTO_TEST_CASE(assigners)
{
  Matrix< int > mtx1(2, 2, 1);
  Matrix< int > mtx2(2, 2);
  mtx2 = mtx1;
  BOOST_TEST(mtx2.size() == mtx1.size());

  Matrix< int > mtx3(2, 2);
  mtx3 = std::move(mtx1);
  BOOST_TEST(mtx3.size() == 4);
  BOOST_TEST(mtx1.empty());
}

BOOST_AUTO_TEST_CASE(fill)
{
  Matrix< int > mtx1(2, 2);
  mtx1.fill(1);
  mtx1.fill(2);
}

BOOST_AUTO_TEST_CASE(empty_rows_cols_size)
{
  Matrix< int > mtx(2, 3);
  BOOST_TEST(!mtx.empty());
  BOOST_TEST(mtx.rows() == 2);
  BOOST_TEST(mtx.cols() == 3);
  BOOST_TEST(mtx.size() == 6);
}

BOOST_AUTO_TEST_CASE(clear)
{
  Matrix< int > mtx(2, 3);
  mtx.clear();
  mtx.clear();
  BOOST_TEST(!mtx.empty());
}
