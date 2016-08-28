#include <gtest/gtest.h>

#include "engine/vect3.h"

using namespace zi;

class Vect3Test : public testing::Test
{
protected:
    virtual void SetUp()
    {
    }
    
    virtual void TearDown()
    {
    }
};

TEST_F(Vect3Test, testAdding)
{
    Vect3<int> vect1(1, 2, 2);
    Vect3<int> vect2(2, 3, 3);
    
    Vect3<int> test1 = vect1 + vect2;
    Vect3<int> test2 = test1;
    test2 += vect1;
    Vect3<int> test3 = vect1 + 2;
    
    Vect3<int> result1(3, 5, 5);
    Vect3<int> result2(4, 7, 7);
    Vect3<int> result3(3, 4, 4);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
    ASSERT_EQ(result3, test3);
}

TEST_F(Vect3Test, testSubtracking)
{
    Vect3<int> vect1(4, 7, 4);
    Vect3<int> vect2(3, 5, 3);
    
    Vect3<int> test1 = vect1 - vect2;
    Vect3<int> test2 = test1;
    test2 -= vect1;
    Vect3<int> test3 = vect1 - 5;
    
    Vect3<int> result1(1, 2, 1);
    Vect3<int> result2(-3, -5, -3);
    Vect3<int> result3(-1, 2, -1);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
    ASSERT_EQ(result3, test3);
}

TEST_F(Vect3Test, testMultiplaying)
{
    Vect3<int> vect1(1, 2, 2);
    Vect3<int> vect2(2, 3, 3);
    
    Vect3<int> test1 = vect1 * vect2;
    Vect3<int> test2 = test1;
    test2 *= vect2;
    Vect3<int> test3 = test1 * 2;
    
    Vect3<int> result1(2, 6, 6);
    Vect3<int> result2(4, 18, 18);
    Vect3<int> result3(2, 4, 4);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
    ASSERT_EQ(result3, test3);
}

TEST_F(Vect3Test, testDividing)
{
    Vect3<float> vect1(4.0f, 9.0f, 9.0f);
    Vect3<float> vect2(2.0f, 3.0f, 2.0f);
    
    Vect3<float> test1 = vect1 / vect2;
    Vect3<float> test2 = test1;
    test2 /= vect2;
    Vect3<float> test3 = vect1 / 2;
    
    Vect3<float> result1(2.0f, 3.0f, 4.5f);
    Vect3<float> result2(1.0f, 1.0f, 2.25f);
    Vect3<float> result3(1.0f, 4.5f, 4.5f);
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
    ASSERT_EQ(result3, test3);
}

TEST_F(Vect3Test, testLength)
{
    /*
     * This can be better nubers for testing
     */
    Vect3<int> vect1(4, 3, 0);
    Vect3<float> vect2(1.5f, 2.0f, 0.0f);
    
    float result1 = 5.0f;
    float result2 = 2.5f;
    
    float test1 = vect1.length();
    float test2 = vect2.length();
    
    ASSERT_EQ(result1, test1);
    ASSERT_EQ(result2, test2);
}

TEST_F(Vect3Test, testNormalizing)
{
    Vect3<float> vect1(5.0f, 3.0f, 2.0f);
    Vect3<float> vect2(1.23f, 3.2876f, 7.89);
    
    vect1.normalize();
    vect2.normalize();
    
    float result = 1.0f;
    
    ASSERT_FLOAT_EQ(result, vect1.length());
    ASSERT_FLOAT_EQ(result, vect2.length());
}
