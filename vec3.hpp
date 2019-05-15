#pragma once

#include <math.h>
#include <iostream>

template <typename T=double>
class vec3 {
public:
    vec3(T e0, T e1, T e2) : e{e0,e1,e2} {}

    inline T x() const { return e[0]; }
    inline T y() const { return e[1]; }
    inline T z() const { return e[2]; }

    inline T r() const { return e[0]; }
    inline T g() const { return e[1]; }
    inline T b() const { return e[2]; }

    inline const vec3<T>& operator+() const { return *this; }
    inline vec3<T> operator-() const { return vec3<T>(-e[0], -e[1], -e[2]); }
    inline T operator[](int i) const { return i<3?e[i]:std::runtime_error("Out of bounds access");}
    inline T& operator[](int i) {return i<3?e[i]:std::runtime_error("Out of bounds access");}
    
    inline vec3<T> operator+ (const vec3<T>& v2) const;
    inline vec3<T> operator- (const vec3<T>& v2) const;
    inline vec3<T> operator* (const vec3<T>& v2) const;
    inline vec3<T> operator/ (const vec3<T>& v2) const;

    inline vec3<T>& operator+=(const vec3<T>& v2);
    inline vec3<T>& operator-=(const vec3<T>& v2);
    inline vec3<T>& operator*=(const vec3<T>& v2);
    inline vec3<T>& operator/=(const vec3<T>& v2);
    inline vec3<T>& operator*=(const T v2);
    inline vec3<T>& operator/=(const T v2);
    
    inline T length() const{
        return sqrt(squared_length());
    }

    inline T squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline void make_unit_vector();
private:    
    T e[3];
};

template<typename T = double>
inline vec3<T> operator*(T t, const vec3<T>& v){
    return vec3<T>(t*v.x(),
                   t*v.y(),
                   t*v.z());
}


template<typename T>
inline std::istream& operator>>(std::istream& is, vec3<T> &t){
    is >> t[0] >> t[1] >> t[2];
    return is;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const vec3<T>& t){
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

template<typename T>
inline void vec3<T>::make_unit_vector(){
    T k = 1.0 / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

template<typename T>
inline vec3<T> vec3<T>::operator+(const vec3<T>& v2) const{
    return vec3<T>(x() + v2.x(),
                   y() + v2.y(),
                   z() + v2.z());
}

template<typename T>
inline vec3<T> vec3<T>::operator-(const vec3<T>& v2) const {
    return vec3<T>(x() - v2.x(),
                   y() - v2.y(),
                   z() - v2.z());
}

template<typename T>
inline vec3<T> vec3<T>::operator*(const vec3<T>& v2) const {
    return vec3<T>(x() * v2.x(),
                   y() * v2.y(),
                   z() * v2.z());
}

template<typename T>
inline vec3<T> vec3<T>::operator/(const vec3<T>& v2) const {
    return vec3<T>(x() / v2.x(),
                   y() / v2.y(),
                   z() / v2.z());
}

template<typename T>
inline vec3<T> operator/(const vec3<T>& v, T t){
    return vec3<T>(v.x()/t,
                   v.y()/t,
                   v.z()/t);
}

template<typename T>
inline vec3<T> operator*(const vec3<T>& v, T t){
    return vec3<T>(t*v.x(),
                   t*v.y(),
                   t*v.z());
}

template<typename T>
inline T dot(const vec3<T>& v1, const vec3<T>& v2){
    return v1.x() * v2.x() + 
           v1.y() * v2.y() + 
           v1.z() * v2.z();
}

template<typename T>
inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2){
    return vec3<T>( (v1.y()*v2.z() - v1.z()*v2.y()),
                 -(v1.x()*v2.z() - v1.z()*v2.x()),
                 v1.x()*v2.y() - v1.y()*v2.x());
}

template<typename T>
inline vec3<T>& vec3<T>::operator+=(const vec3<T>& v){
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator-=(const vec3<T>& v){
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator*=(const vec3<T>& v){
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator/=(const vec3<T>& v){
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator*=(const T t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

template<typename T>
inline vec3<T>& vec3<T>::operator/=(const T t){
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

template <typename T=double>
inline vec3<T> unit_vector(vec3<T> v){
    return v/v.length();
}