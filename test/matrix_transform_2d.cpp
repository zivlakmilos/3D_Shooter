#include <gtest/gtest.h>

#include "engine/core/core.h"

using namespace zi;

class MatrixTransformTest2D : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
};

TEST_F(MatrixTransformTest2D, rotate)
{
    Vect2<int> vect1(2, 3);
    Matrix<int, 2, 2> matrix1 = Matrix<int, 2, 2>::rotateCW2D(90);
    Vect2<float> vect2(1, 0);
    Matrix<float, 2, 2> matrix2 = Matrix<float, 2, 2>::rotateCW2D(180);
    
    Vect2<int> result1(3, -2);
    Vect2<int> test1 = matrix1 * vect1;
    
    Vect2<float> result2(-1, 0);
    Vect2<float> test2 = matrix2 * vect2;
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}
