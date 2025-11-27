#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m1(3);
  for (size_t i = 0; i < m1.size(); i++)
    for (size_t j = 0; j < m1.size(); j++)
      m1[i][j] = i * m1.size() + j + 1;
  
  TDynamicMatrix<int> m2(m1);
  
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 100;
  
  EXPECT_NE(m1[0][0], m2[0][0]);
  EXPECT_EQ(1, m1[0][0]);
  EXPECT_EQ(100, m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);
  
  EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 5;
  m[1][2] = 10;
  
  EXPECT_EQ(5, m[0][0]);
  EXPECT_EQ(10, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  
  ASSERT_ANY_THROW(m[0].at(-1));
  ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  
  ASSERT_ANY_THROW(m[0].at(10));
  ASSERT_ANY_THROW(m.at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  
  ASSERT_NO_THROW(m = m);
  
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[0][1]);
  EXPECT_EQ(3, m[1][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  m2 = m1;
  
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(4);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  m2 = m1;
  
  EXPECT_EQ(2, m2.size());
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  m2 = m1;
  
  EXPECT_EQ(2, m2.size());
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 1; m2[0][1] = 2;
  m2[1][0] = 3; m2[1][1] = 4;
  
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  
  EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 5; m2[0][1] = 6;
  m2[1][0] = 7; m2[1][1] = 8;
  
  TDynamicMatrix<int> m3 = m1 + m2;
  
  EXPECT_EQ(6, m3[0][0]);
  EXPECT_EQ(8, m3[0][1]);
  EXPECT_EQ(10, m3[1][0]);
  EXPECT_EQ(12, m3[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 5; m1[0][1] = 6;
  m1[1][0] = 7; m1[1][1] = 8;
  m2[0][0] = 1; m2[0][1] = 2;
  m2[1][0] = 3; m2[1][1] = 4;
  
  TDynamicMatrix<int> m3 = m1 - m2;
  
  EXPECT_EQ(4, m3[0][0]);
  EXPECT_EQ(4, m3[0][1]);
  EXPECT_EQ(4, m3[1][0]);
  EXPECT_EQ(4, m3[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 5; m2[0][1] = 6;
  m2[1][0] = 7; m2[1][1] = 8;
  
  TDynamicMatrix<int> m3 = m1 * m2;
  
  // Проверка: [1 2] * [5 6] = [1*5+2*7 1*6+2*8] = [19 22]
  //           [3 4]   [7 8]   [3*5+4*7 3*6+4*8]   [43 50]
  EXPECT_EQ(19, m3[0][0]);
  EXPECT_EQ(22, m3[0][1]);
  EXPECT_EQ(43, m3[1][0]);
  EXPECT_EQ(50, m3[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  
  ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  TDynamicMatrix<int> m2 = m1 * 3;
  
  EXPECT_EQ(3, m2[0][0]);
  EXPECT_EQ(6, m2[0][1]);
  EXPECT_EQ(9, m2[1][0]);
  EXPECT_EQ(12, m2[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  v[0] = 5; v[1] = 6;
  
  TDynamicVector<int> result = m * v;
  
  // [1 2] * [5] = [1*5 + 2*6] = [17]
  // [3 4]   [6]   [3*5 + 4*6]   [39]
  EXPECT_EQ(17, result[0]);
  EXPECT_EQ(39, result[1]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_different_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(3);
  
  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_use_move_constructor)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  TDynamicMatrix<int> m2(std::move(m1));
  
  EXPECT_EQ(2, m2.size());
  EXPECT_EQ(1, m2[0][0]);
  EXPECT_EQ(2, m2[0][1]);
  EXPECT_EQ(3, m2[1][0]);
  EXPECT_EQ(4, m2[1][1]);
  EXPECT_EQ(0, m1.size());
}

TEST(TDynamicMatrix, can_use_move_assignment)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  m2 = std::move(m1);
  
  EXPECT_EQ(2, m2.size());
  EXPECT_EQ(1, m2[0][0]);
  EXPECT_EQ(2, m2[0][1]);
  EXPECT_EQ(3, m2[1][0]);
  EXPECT_EQ(4, m2[1][1]);
  EXPECT_EQ(0, m1.size());
}

TEST(TDynamicMatrix, can_use_input_output_operators)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  std::stringstream ss;
  ss << m1;
  
  TDynamicMatrix<int> m2(2);
  ss >> m2;
  
  EXPECT_EQ(m1, m2);
}
