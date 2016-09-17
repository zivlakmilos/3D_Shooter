#ifndef _ENGINE_CORE_VECT2_H_
#define _ENGINE_CORE_VECT2_H_

#include <ostream>
#include <cmath>

#include "engine/core/constants.h"

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
        
        Vect2(const Vect2<T> &vect)
            : Vect2(vect.getX(), vect.getY())
        {
        }
        
        virtual ~Vect2(void)
        {
        }
        
        /*
         * Getters and setters
         */
        virtual T getX(void) const { return m_x; };
        virtual void setX(T x) { m_x = x; };
        virtual T getY(void) const { return m_y; };
        virtual void setY(T y) { m_y = y; };
        
        virtual float length(void) const
        {
            return sqrt(getX() * getX() +
                        getY() * getY());
        }
        
        virtual void normalize(void)    // Not work for integer vectors
        {
            *this /= length();
        }
        
        virtual T dotProduct(const Vect2<T> &vect) const
        {
            return getX() * vect.getX() + getY() * vect.getY();
        }
        
        virtual T crossProduct(const Vect2<T> &vect) const
        {
            return getX() * vect.getY() - getY() * vect.getX();
        }
        
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
        
        Vect2<T> &operator+=(const T &rhs)
        {
            setX(getX() + rhs);
            setY(getY() + rhs);
            
            return *this;
        }
        
        Vect2<T> operator+(const T &rhs)
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
        
        Vect2<T> &operator-=(const T &rhs)
        {
            setX(getX() - rhs);
            setY(getY() - rhs);
            
            return *this;
        }
        
        Vect2<T> operator-(const T &rhs)
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
        
        Vect2<T> &operator*=(const T &rhs)
        {
            setX(getX() * rhs);
            setY(getY() * rhs);
            
            return *this;
        }
        
        Vect2<T> operator*(const T &rhs)
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
        
        Vect2<T> &operator/=(const T &rhs)
        {
            setX(getX() / rhs);
            setY(getY() / rhs);
            
            return *this;
        }
        
        Vect2<T> operator/(const T &rhs)
        {
            Vect2<T> result(*this);
            
            result /= rhs;
            
            return result;
        }
        
        friend std::ostream &operator<<(std::ostream &output, const Vect2<T> &rhs)
        {
            output << "[ " << rhs.getX()
                   << ", " << rhs.getY() << " ]";
            
            return output;
        }
        
    protected:
        T m_x;
        T m_y;
    };
    
    /*
     * For easyer use
     */
    typedef Vect2<int> Vect2i;
    typedef Vect2<float> Vect2f;
}

#endif // _ENGINE_CORE_VECT2_H_
