#pragma once

#include "ray.hpp"
#include <memory>

struct hit_record{
    double t;
    vec3 p;
    vec3 normal;
};

class hitable {
    public:
        typedef std::shared_ptr<hitable> Ptr;
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};