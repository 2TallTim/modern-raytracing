#pragma once

#include <math.h>
#include <iostream>

class vec3 {
public:
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

    inline double x() const { return e[0]; }
    inline double y() const { return e[1]; }
    inline double z() const { return e[2]; }

    inline double r() const { return e[0]; }
    inline double g() const { return e[1]; }
    inline double b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline double operator[](int i) const { return e[i];}
    inline double& operator[](int i) {return e[i];}
    
    inline vec3 operator+ (const vec3& v2) const;
    inline vec3 operator- (const vec3& v2) const;
    inline vec3 operator* (const vec3& v2) const;
    inline vec3 operator/ (const vec3& v2) const;

    inline vec3& operator+=(const vec3& v2);
    inline vec3& operator-=(const vec3& v2);
    inline vec3& operator*=(const vec3& v2);
    inline vec3& operator/=(const vec3& v2);
    inline vec3& operator*=(const double v2);
    inline vec3& operator/=(const double v2);
    
    inline double length() const{
        return sqrt(squared_length());
    }

    inline double squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline void make_unit_vector();
private:    
    double e[3];
};

inline vec3 operator*(double t, const vec3& v){
    return vec3(t*v.x(),
                   t*v.y(),
                   t*v.z());
}

inline std::istream& operator>>(std::istream& is, vec3 &t){
    is >> t[0] >> t[1] >> t[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t){
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

inline void vec3::make_unit_vector(){
    double k = 1.0 / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 vec3::operator+(const vec3& v2) const{
    return vec3(x() + v2.x(),
                   y() + v2.y(),
                   z() + v2.z());
}

inline vec3 vec3::operator-(const vec3& v2) const {
    return vec3(x() - v2.x(),
                   y() - v2.y(),
                   z() - v2.z());
}

inline vec3 vec3::operator*(const vec3& v2) const {
    return vec3(x() * v2.x(),
                   y() * v2.y(),
                   z() * v2.z());
}

inline vec3 vec3::operator/(const vec3& v2) const {
    return vec3(x() / v2.x(),
                   y() / v2.y(),
                   z() / v2.z());
}

inline vec3 operator/(const vec3& v, double t){
    return vec3(v.x()/t,
                   v.y()/t,
                   v.z()/t);
}

inline vec3 operator*(const vec3& v, double t){
    return vec3(t*v.x(),
                   t*v.y(),
                   t*v.z());
}

inline double dot(const vec3& v1, const vec3& v2){
    return v1.x() * v2.x() + 
           v1.y() * v2.y() + 
           v1.z() * v2.z();
}

inline vec3 cross(const vec3& v1, const vec3& v2){
    return vec3( (v1.y()*v2.z() - v1.z()*v2.y()),
                 -(v1.x()*v2.z() - v1.z()*v2.x()),
                 v1.x()*v2.y() - v1.y()*v2.x());
}

inline vec3& vec3::operator+=(const vec3& v){
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v){
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

inline vec3& vec3::operator*=(const vec3& v){
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;
}

inline vec3& vec3::operator/=(const vec3& v){
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;
}

inline vec3& vec3::operator*=(const double t){
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/=(const double t){
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

inline vec3 unit_vector(vec3 v){
    return v/v.length();
}