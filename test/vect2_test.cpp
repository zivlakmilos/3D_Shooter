#include <gtest/gtest.h>

#include "engine/vect2.h"

using namespace zi;

class Vect2Test : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
};

TEST_F(Vect2Test, testAdding)
{
    Vect2<int> vect1(1, 2);
    Vect2<int> vect2(2, 3);
    
    Vect2<int> test1 = vect1 + vect2;
    Vect2<int> test2 = test1;
    test2 += vect1;
    
    Vect2<int> result1(3, 5);
    Vect2<int> result2(4, 7);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}

TEST_F(Vect2Test, testSubtracking)
{
    Vect2<int> vect1(4, 7);
    Vect2<int> vect2(3, 5);
    
    Vect2<int> test1 = vect1 - vect2;
    Vect2<int> test2 = test1;
    test2 -= vect1;
    
    Vect2<int> result1(1, 2);
    Vect2<int> result2(-3, -5);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}

TEST_F(Vect2Test, testMultiplaying)
{
    Vect2<int> vect1(1, 2);
    Vect2<int> vect2(2, 3);
    
    Vect2<int> test1 = vect1 * vect2;
    Vect2<int> test2 = test1;
    test2 *= vect2;
    
    Vect2<int> result1(2, 6);
    Vect2<int> result2(4, 18);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}

TEST_F(Vect2Test, testDividing)
{
    Vect2<float> vect1(4.0f, 9.0f);
    Vect2<float> vect2(2.0f, 2.0f);
    
    Vect2<float> test1 = vect1 / vect2;
    Vect2<float> test2 = test1;
    test2 /= vect2;
    
    Vect2<float> result1(2.0f, 4.5f);
    Vect2<float> result2(1.0f, 2.25f);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}

TEST_F(Vect2Test, testLength)
{
    Vect2<int> vect1(4, 3);
    Vect2<float> vect2(1.5f, 2.0f);
    
    float result1 = 5.0f;
    float result2 = 2.5f;
    
    float test1 = vect1.length();
    float test2 = vect2.length();
    
    ASSERT_FLOAT_EQ(result1, test1);
    ASSERT_FLOAT_EQ(result2, test2);
}

TEST_F(Vect2Test, testNormalizing)
{
    Vect2<float> vect1(5.0f, 3.0f);
    Vect2<float> vect2(1.23f, 3.2876f);
    
    vect1.normalize();
    vect2.normalize();
    
    float result = 1.0f;
    
    ASSERT_FLOAT_EQ(result, vect1.length());
    ASSERT_FLOAT_EQ(result, vect2.length());
}
