#pragma once

#include "vec3.hpp"

class ray{
  public:
    ray(){}
    ray(const vec3& a, const vec3& b) : O(a), D(b) {}
    vec3 origin() const { return O; }
    vec3 direction() const { return D; }
    vec3 point_at_parameter(double t) const { return O + t*D; }
    static inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
        vec3 uv = unit_vector(v);
        double dt = dot(uv,n);
        double discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
        if(discriminant > 0){
            refracted = ni_over_nt * (uv - n*dt) - n*sqrt(discriminant);
            return true;
        }
        return false;
    }

    static inline vec3 reflect(const vec3& v, const vec3& n){
        return v - 2*dot(v,n)*n;
    }

    static inline double schlick(double cosine, double ref_idx){
        double r0 = (1-ref_idx) / (1+ref_idx);
        r0 *= r0;
        return r0 + (1-r0) * pow((1-cosine),5);
    }
  private:
    vec3 O; // Ray origin
    vec3 D; // Ray direction
};