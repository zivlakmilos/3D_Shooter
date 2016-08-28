#ifndef _VECT3_H_
#define _VECT3_H_

#include "engine/vect2.h"

#include <ostream>

namespace zi
{
    /*
     * Vect3 is class for holding data about 3D vectors
     * 
     * Musb be implemented in header becouse of templates!
     */
    template<typename T>
    class Vect3 : public Vect2<T>
    {
    public:
        Vect3(void)
            : Vect3(0, 0, 0)
        {
        }
        
        /*
         * Main constructors, all other call them
         * only edit here!
         */
        Vect3(T x, T y, T z)
            : Vect2<T>(x, y),
              m_z(z)
        {
        }
        
        Vect3(const Vect3<T> &vect)
            : Vect3(vect.getX(), vect.getY(), vect.getZ())
        {
        }
        
        ~Vect3(void)
        {
        }
        
        /*
         * Getters and setters
         */
        virtual T getZ(void) const { return m_z; };
        virtual void setZ(T z) { m_z = z; };
        
        virtual float length(void) const
        {
            return sqrt(this->getX() * this->getX() +
                        this->getY() * this->getY() +
                        getZ() * getZ());
        }
        
        virtual void normalize(void)    // Not work for integer vectors
        {
            float len = length();
            
            this->setX(this->getX() / len);
            this->setY(this->getY() / len);
            setZ(getZ() / len);
        }
        
        bool operator==(const Vect3<T> &rhs) const
        {
            return this->getX() == rhs.getX() &&
                   this->getY() == rhs.getY() &&
                   getZ() == rhs.getZ();
        }
        
        Vect3<T> &operator=(const Vect3<T> &rhs)
        {
            if(this != &rhs)
            {   this->setX(rhs.getX());
                this->setY(rhs.getY());
                setZ(rhs.getZ());
            }
            
            return *this;
        }
        
        Vect3<T> &operator+=(const Vect3<T> &rhs)
        {
            this->setX(this->getX() + rhs.getX());
            this->setY(this->getY() + rhs.getY());
            setZ(getZ() + rhs.getZ());
            
            return *this;
        }
        
        Vect3<T> operator+(const Vect3<T> &rhs)
        {
            Vect3<T> result(*this);
            
            result += rhs;
            
            return result;
        }
        
        Vect2<T> &operator+=(const T &rhs)
        {
            this->setX(this->getX() + rhs);
            this->setY(this->getY() + rhs);
            setZ(getZ() + rhs);
            
            return *this;
        }
        
        Vect2<T> operator+(const T &rhs)
        {
            Vect2<T> result(*this);
            
            result += rhs;
            
            return result;
        }
        
        Vect3<T> &operator-=(const Vect3<T> &rhs)
        {
            this->setX(this->getX() - rhs.getX());
            this->setY(this->getY() - rhs.getY());
            setZ(getZ() - rhs.getZ());
            
            return *this;
        }
        
        Vect3<T> operator-(const Vect3<T> &rhs)
        {
            Vect3<T> result(*this);
            
            result -= rhs;
            
            return result;
        }
        
        Vect2<T> &operator-=(const T &rhs)
        {
            this->setX(this->getX() - rhs);
            this->setY(this->getY() - rhs);
            setZ(getZ() - rhs);
            
            return *this;
        }
        
        Vect2<T> operator-(const T &rhs)
        {
            Vect2<T> result(*this);
            
            result -= rhs;
            
            return result;
        }
        
        Vect3<T> &operator*=(const Vect3<T> &rhs)
        {
            this->setX(this->getX() * rhs.getX());
            this->setY(this->getY() * rhs.getY());
            setZ(getZ() * rhs.getZ());
            
            return *this;
        }
        
        Vect3<T> operator*(const Vect3<T> &rhs)
        {
            Vect3<T> result(*this);
            
            result *= rhs;
            
            return result;
        }
        
        Vect2<T> &operator*=(const T &rhs)
        {
            this->setX(this->getX() * rhs);
            this->setY(this->getY() * rhs);
            setZ(getZ() * rhs);
            
            return *this;
        }
        
        Vect2<T> operator*(const T &rhs)
        {
            Vect2<T> result(*this);
            
            result *= rhs;
            
            return result;
        }
        
        Vect3<T> &operator/=(const Vect3<T> &rhs)
        {
            this->setX(this->getX() / rhs.getX());
            this->setY(this->getY() / rhs.getY());
            setZ(getZ() / rhs.getZ());
            
            return *this;
        }
        
        Vect3<T> operator/(const Vect3<T> &rhs)
        {
            Vect3<T> result(*this);
            
            result /= rhs;
            
            return result;
        }
        
        Vect2<T> &operator/=(const T &rhs)
        {
            this->setX(this->getX() / rhs);
            this->setY(this->getY() / rhs);
            setZ(getZ() / rhs);
            
            return *this;
        }
        
        Vect2<T> operator/(const T &rhs)
        {
            Vect2<T> result(*this);
            
            result /= rhs;
            
            return result;
        }
        
        friend std::ostream &operator<<(std::ostream &output, const Vect3<T> &rhs)
        {
            output << "[ " << rhs.getX()
                   << ", " << rhs.getY()
                   << ", " << rhs.getZ()
                   << " ]" << std::endl;
            
            return output;
        }
        
    protected:
        T m_z;
    };
    
    /*
     * For easyer use
     */
    typedef Vect3<int> Vect3i;
    typedef Vect3<float> Vect3f;
}

#endif // _VECT3_H_
