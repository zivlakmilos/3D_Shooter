#ifndef _ENGINE_CORE_MATRIX_H_
#define _ENGINE_CORE_MATRIX_H_

#include <initializer_list>
#include <ostream>
#include <cmath>

#include "engine/core/vect4.h"
#include "engine/errors/errors.h"

namespace zi
{
    /*
     * Class for holding matrix data
     */
    template<typename T, int rows = 2, int columns = 2>
    class Matrix
    {
    public:
        Matrix(void);
        Matrix(std::initializer_list<T> initList);
        Matrix(const Matrix<T, rows, columns> &matrix);
        ~Matrix(void);
        
        Matrix<T, rows, columns> operator=(const Matrix &matrix);
        Matrix<T, rows, columns> operator=(const std::initializer_list<T> initList);
        
        /*
         * 2D transform matrices
         */
        static Matrix<float, 2, 2> rotateCW2D(float angle);
        static Matrix<float, 2, 2> rotateCCW2D(float angle);
        static Matrix<float, 2, 2> reflectionX2D(void);
        static Matrix<float, 2, 2> reflectionY2D(void);
        static Matrix<float, 2, 2> scale2D(float value);
        
        /*
         * 3D transform matrices
         */
        
        /*
         * Proxy classes
         */
        class MatrixRow
        {
            friend Matrix;
            
        public:
            MatrixRow(const Matrix<T, rows, columns> &parent, const int &row)
                : m_parent(parent),
                  m_row(row)
            {
            }
            
            class Proxy
            {
                friend Matrix;
                
            public:
                Proxy(const Matrix<T, rows, columns> &parent, const int &row, const int &column)
                    : m_parent(parent),
                      m_row(row),
                      m_column(column)
                {
                }
                
                operator T() const
                {
                    return m_parent.m_matrix[m_row][m_column];
                }
                
                void operator=(T value)
                {
                    m_parent.m_matrix[m_row][m_column] = value;
                }
                
            private:
                Matrix<T, rows, columns> m_parent;
                int m_row;
                int m_column;
            };
            
            Proxy operator[](const int &column) const
            {
                return Proxy(m_parent, m_row, column);
            }
            
        private:
            Matrix<T, rows, columns> m_parent;
            int m_row;
        };
        
        /*
         * Must be here!
         */
        MatrixRow operator[](const int &row) const
        {
            return MatrixRow(*this, row);
        }
        
    private:
        T m_matrix[rows][columns];
    };
    
    /*
     * Operators
     */
    
    template<typename T>
    Vect4<T> operator*(const Matrix<T, 4, 4> &lhs, const Vect4<T> &rhs)
    {
        Vect4<T> result;
        
        result.setX(lhs[0][0] * rhs.getX() +
                    lhs[0][1] * rhs.getY() +
                    lhs[0][2] * rhs.getZ() +
                    lhs[0][3] * rhs.getW());
        result.setY(lhs[1][0] * rhs.getX() +
                    lhs[1][1] * rhs.getY() +
                    lhs[1][2] * rhs.getZ() +
                    lhs[1][3] * rhs.getW());
        result.setZ(lhs[2][0] * rhs.getX() +
                    lhs[2][1] * rhs.getY() +
                    lhs[2][2] * rhs.getZ() +
                    lhs[2][3] * rhs.getW());
        result.setW(lhs[3][0] * rhs.getX() +
                    lhs[3][1] * rhs.getY() +
                    lhs[3][2] * rhs.getZ() +
                    lhs[3][3] * rhs.getW());
        
        return result;
    }
    
    template<typename T>
    Vect2<T> operator*(const Matrix<T, 2, 2> &lhs, const Vect2<T> &rhs)
    {
        Vect2<T> result;
        
        result.setX(lhs[0][0] * rhs.getX() +
                    lhs[0][1] * rhs.getY());
        result.setY(lhs[1][0] * rhs.getX() +
                    lhs[1][1] * rhs.getY());
        
        return result;
    }
    
    /*
     * For easyer use
     */
    typedef Matrix<int, 2, 2> Matrix2i;
    typedef Matrix<float, 2, 2> Matrix2f;
    typedef Matrix<int, 3, 3> Matrix3i;
    typedef Matrix<float, 3, 3> Matrix3f;
}

/*
 * Implementation
 */

template<typename T, int rows, int columns>
zi::Matrix<T, rows, columns>::Matrix(void)
{
    int i, j;
    for(i = 0; i < rows; i++)
        for(j = 0; j < columns; j++)
            m_matrix[i][j] = 0;
}

template<typename T, int rows, int columns>
zi::Matrix<T, rows, columns>::Matrix(std::initializer_list<T> initList)
{
    int i = 0, j = 0;
    for(auto item : initList)
    {
        m_matrix[i][j] = item;
        if(++j >= columns)
        {
            j = 0;
            if(++i >= rows)
                break;
        }
    }
    // All others are zero (0)
    for(; i < rows; i++)
        for(; j < columns; j++)
            m_matrix[i][j] = 0;
}

template<typename T, int rows, int columns>
zi::Matrix<T, rows, columns>::Matrix(const Matrix<T, rows, columns> &matrix)
{
    int i, j;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            m_matrix[i][j] = matrix.m_matrix[i][j];
        }
    }
}

template<typename T, int rows, int columns>
zi::Matrix<T, rows, columns>::~Matrix(void)
{
}

template<typename T, int rows, int columns>
std::ostream &operator<<(
        std::ostream &output,
        zi::Matrix<T, rows, columns> &rhs)
{
    int i, j;
    
    for(i = 0; i < rows; i++)
    {
        if(i == 0)
            output << "[ ";
        else
            output << "  ";
        for(j = 0; j < columns; j++)
        {
            output << rhs[i][j];
            if(j == columns - 1 && i == rows - 1)
                output << " ]";
            else
                output << ", ";
        }
        output << std::endl;
    }
    
    return output;
}

template<typename T, int rows, int columns>
zi::Matrix<float, 2, 2> zi::Matrix<T, rows, columns>::rotateCW2D(float angle)
{
    float rad = angle * zi::PI / 180.0f;
    
    return Matrix({
         cos(rad), sin(rad),
        -sin(rad), cos(rad)
    });
}

template<typename T, int rows, int columns>
zi::Matrix<float, 2, 2> zi::Matrix<T, rows, columns>::rotateCCW2D(float angle)
{
    float rad = angle * zi::PI / 180.0f;
    
    return Matrix({
        cos(rad), -sin(rad),
        sin(rad),  cos(rad)
    });
}

template<typename T, int rows, int columns>
zi::Matrix<float, 2, 2> zi::Matrix<T, rows, columns>::reflectionX2D(void)
{
    return Matrix<float, 2, 2>({
        1,  0,
        0, -1
    });
}

template<typename T, int rows, int columns>
zi::Matrix<float, 2, 2> zi::Matrix<T, rows, columns>::reflectionY2D(void)
{
    return Matrix<float, 2, 2>({
        -1, 0,
         0, 1
    });
}

template<typename T, int rows, int columns>
zi::Matrix<float, 2, 2> zi::Matrix<T, rows, columns>::scale2D(float value)
{
    return Matrix<float, 2, 2>({
        value, 0,
        0, value
    });
}

#endif // _ENGINE_CORE_MATRIX_H_
