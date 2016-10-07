#ifndef _ENGINE_CORE_VECT4_H_
#define _ENGINE_CORE_VECT4_H_

#include "engine/core/math/vect3.h"

namespace zi
{
    /*
     * Class for holding 3D vector data with homogenous corrdinate
     */
    template<typename T>
    class Vect4 : public Vect3<T>
    {
    public:
        Vect4(void);
        Vect4(T x, T y, T z, int w = 0);
        Vect4(Vect4<T> &vect);
        virtual ~Vect4(void);
        
        virtual int getW(void) const { return m_w; };
        void setW(int w) { m_w = w; };
        virtual Vect3<T> getXYZ(void) const { return Vect3<T>(this->getX(), this->getY(), this->getZ()); };
        
        template<typename U>
        bool operator==(Vect4<U> &rhs);
        template<typename U>
        Vect4<T> &operator=(Vect4<U> &rhs);
        
        template<typename U>
        Vect4<T> &operator+=(Vect4<U> &rhs);
        template<typename U>
        Vect4<T> &operator+=(U &rhs);
        template<typename U>
        Vect4<T> &operator-=(Vect4<U> &rhs);
        template<typename U>
        Vect4<T> &operator-=(U &rhs);
        template<typename U>
        Vect4<T> &operator*=(Vect4<U> &rhs);
        template<typename U>
        Vect4<T> &operator*=(U &rhs);
        template<typename U>
        Vect4<T> &operator/=(Vect4<U> &rhs);
        template<typename U>
        Vect4<T> &operator/=(U &rhs);
        
    protected:
        int m_w;
    };
    
    /*
     * For easyer use
     */
    typedef Vect4<int> Vect4i;
    typedef Vect4<float> Vect4f;
}

/*
 * Implementation
 */

template<typename T>
zi::Vect4<T>::Vect4(void)
    : Vect4(0, 0, 0, 0)
{
}

template<typename T>
zi::Vect4<T>::Vect4(T x, T y, T z, int w)
    : zi::Vect3<T>(x, y, z),
      m_w(w)
{
}

template<typename T>
zi::Vect4<T>::Vect4(Vect4<T> &vect)
    : Vect4(vect.getX(), vect.getY(), vect.getZ(), vect.getW())
{
}

template<typename T>
zi::Vect4<T>::~Vect4(void)
{
}

template<typename T>
template<typename U>
bool zi::Vect4<T>::operator==(Vect4<U> &rhs)
{
    return zi::Vect3<T>::operator==(rhs.getXYZ() && getW()) == rhs.getW();
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator=(Vect4<U> &rhs)
{
    if(this != &rhs)
    {
        this->setX(static_cast<T>(rhs.getX()));
        this->setY(static_cast<T>(rhs.getY()));
        this->setZ(static_cast<T>(rhs.getZ()));
        setW(rhs.getW());
    }
    
    return *this;
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator+=(Vect4<U> &rhs)
{
    return Vect3<T>::operator+=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator+=(U &rhs)
{
    return Vect3<T>::operator+=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator-=(Vect4<U> &rhs)
{
    return Vect3<T>::operator-=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator-=(U &rhs)
{
    return Vect3<T>::operator-=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator*=(Vect4<U> &rhs)
{
    return Vect3<T>::operator*=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator*=(U &rhs)
{
    return Vect3<T>::operator*=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator/=(Vect4<U> &rhs)
{
    return Vect3<T>::operator/=(rhs);
}

template<typename T>
template<typename U>
zi::Vect4<T> &zi::Vect4<T>::operator/=(U &rhs)
{
    return Vect3<T>::operator/=(rhs);
}

#endif // _ENGINE_CORE_VECT4_H_
