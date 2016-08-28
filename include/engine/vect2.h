#ifndef _VEC2_H_
#define _VEC2_H_

#include <ostream>

namespace zi
{
    /*
     * Vect2 is class for hold data about 2D vector
     * 
     * Musb be implemented in header becouse of templates!
     */
    template<typename T>
    class Vect2
    {
    public:
        Vect2(void)
            : Vect2(0, 0)
        {
        }
        
        /*
         * Main constructor, edit only this, orhers call it
         */
        Vect2(T x, T y)
            : m_x(x),
              m_y(y)
        {
        }
        
        Vect2(const Vect2 &vect)
            : Vect2(vect.getX(), vect.getY())
        {
        }
        
        /*
         * Getters and setters
         */
        T getX(void) const { return m_x; };
        void setX(T x) { m_x = x; };
        T getY(void) const { return m_y; };
        void setY(T y) { m_y = y; };
        
        bool operator==(const Vect2<T> &rhs) const
        {
            return getX() == rhs.getX() && getY() == rhs.getY();
        }
        
        Vect2<T> &operator=(const Vect2<T> &rhs)
        {
            if(this != &rhs)
            {
                setX(rhs.getX());
                setY(rhs.getY());
            }
            
            return *this;
        }
        
        Vect2<T> &operator+=(const Vect2<T> &rhs)
        {
            setX(getX() + rhs.getX());
            setY(getY() + rhs.getY());
            
            return *this;
        }
        
        Vect2<T> operator+(const Vect2<T> &rhs)
        {
            Vect2<T> result(*this);
            
            result += rhs;
            
            return result;
        }
        
        Vect2<T> &operator-=(const Vect2<T> &rhs)
        {
            setX(getX() - rhs.getX());
            setY(getY() - rhs.getY());
            
            return *this;
        }
        
        Vect2<T> operator-(const Vect2<T> &rhs)
        {
            Vect2<T> result(*this);
            
            result -= rhs;
            
            return result;
        }
        
        Vect2<T> &operator*=(const Vect2<T> &rhs)
        {
            setX(getX() * rhs.getX());
            setY(getY() * rhs.getY());
            
            return *this;
        }
        
        Vect2<T> operator*(const Vect2<T> &rhs)
        {
            Vect2<T> result(*this);
            
            result *= rhs;
            
            return result;
        }
        
        Vect2<T> &operator/=(const Vect2<T> &rhs)
        {
            setX(getX() / rhs.getX());
            setY(getY() / rhs.getY());
            
            return *this;
        }
        
        Vect2<T> operator/(const Vect2<T> &rhs)
        {
            Vect2<T> result(*this);
            
            result /= rhs;
            
            return result;
        }
        
        friend std::ostream &operator<<(std::ostream &output, const Vect2<T> &rhs)
        {
            output << "[ " << rhs.getX() << ", " << rhs.getY() << " ]";
            return output;
        }
        
    private:
        T m_x;
        T m_y;
    };
}

#endif // _VEC2_H_
