#pragma once

#include "ray.hpp"

class aabb {
  private:
    vec3 _min,_max;
  public:
    aabb(){}
    aabb(const vec3& a, const vec3& b) : _min(a), _max(b) {}

    vec3 min() const {return _min;}
    vec3 max() const {return _max;}

    bool hit(const ray& r, double tmin, double tmax) const {
        for (int a = 0; a < 3; a++){
            double invD = 1.0 / r.direction()[a];
            double t0 = (_min[a] - r.origin()[a]) * invD;
            double t1 = (_max[a] - r.origin()[a]) * invD;

            if(invD < 0) std::swap(t0,t1);

            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            if (tmax <= tmin) return false;
        }
        return true;
    }
    static aabb surrounding_box(const aabb& box0, const aabb& box1){
        vec3 small( fmin(box0.min().x(), box1.min().x()),
                    fmin(box0.min().y(), box1.min().y()),
                    fmin(box0.min().z(), box1.min().z()));

        vec3 big( fmax(box0.max().x(), box1.max().x()),
                fmax(box0.max().y(), box1.max().y()),
                fmax(box0.max().z(), box1.max().z()));

        return aabb(small,big);
    }
};