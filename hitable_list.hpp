#pragma once

#include "hitable.hpp"
#include <vector>

class hitable_list: public hitable {
  public:
    hitable_list() {}
    virtual bool hit(const ray& r, 
                     double t_min,
                     double t_max, 
                     hit_record& rec) const;
    virtual bool bounding_box(aabb&);
    void add(const hitable::Ptr& p);    
  private:
    std::vector<hitable::Ptr> list;
};