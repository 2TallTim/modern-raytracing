#pragma once

#include "hitable.hpp"
#include "material.hpp"

class sphere: public hitable {
  public:
    sphere(){}
    sphere(vec3 cen, double r, material::Ptr m) : center(cen), radius(r), mat(m) {}

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
    virtual bool bounding_box(aabb& box) const;
  private:  
    vec3 center;
    double radius;
    material::Ptr mat;
};