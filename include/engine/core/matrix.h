#ifndef _ENGINE_CORE_MATRIX_H_
#define _ENGINE_CORE_MATRIX_H_

#include <initializer_list>
#include <ostream>

namespace zi
{
    template<typename T, int rows = 2, int columns = 2>
    class Matrix
    {
    public:
        Matrix(void);
        Matrix(std::initializer_list<T> initList);
        ~Matrix(void);
        
        T *operator[](const int row);
        
    private:
        T m_matrix[rows][columns];
    };
    
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
    int i, j;
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            int listRb = i * j + j;
            if(listRb > initList.size())
                this[i][j] = initList[listRb];
            else this[i][j] = 0;
        }
    }
}

template<typename T, int rows, int columns>
zi::Matrix<T, rows, columns>::~Matrix(void)
{
}

template<typename T, int rows, int columns>
T *zi::Matrix<T, rows, columns>::operator[](const int row)
{
    return m_matrix[row];
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

#endif // _ENGINE_CORE_MATRIX_H_
