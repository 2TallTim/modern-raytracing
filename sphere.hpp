#pragma once

#include "hitable.hpp"

class sphere: public hitable {
  public:
    sphere(){}
    sphere(vec3<> cen, double r) : center(cen), radius(r) {}

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
  private:  
    vec3<> center;
    double radius;
};