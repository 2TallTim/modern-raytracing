#pragma once

#include "ray.hpp"
#include "aabb.hpp"
#include <memory>

class material;

struct hit_record{
    double t;
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
};

class hitable {
    public:
        typedef std::shared_ptr<hitable> Ptr;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        virtual bool bounding_box(aabb& box) const = 0;
};