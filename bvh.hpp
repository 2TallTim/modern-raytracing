#pragma once

#include "aabb.hpp"
#include "hitable.hpp"
#include "rng.hpp"
#include <vector>
#include <algorithm>

class bvh_node : public hitable{ 
    private:
    hitable::Ptr left, right;
    aabb box;
    public:
    bvh_node(std::vector<hitable::Ptr>::iterator begin,
             std::vector<hitable::Ptr>::iterator end);
    virtual bool hit(const ray& r, 
                     double t_min,
                     double t_max, 
                     hit_record& rec) const;
    virtual bool bounding_box(aabb& box) const;
};