#pragma once

#include "hitable.hpp"
#include <list>

class hitable_list: public hitable {
  public:
    hitable_list() {}
    virtual bool hit(const ray& r, 
                     double t_min,
                     double t_max, 
                     hit_record& rec) const;
    void add(const hitable::Ptr& p);
  private:
    std::list<hitable::Ptr> list;
};