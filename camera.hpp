#pragma once

#include "ray.hpp"

class camera{
private:
    vec3<> aim;
    vec3<> origin;
    vec3<> horizontal;
    vec3<> vertical;
public:
    ray get_ray(float u, float v){
        return ray(origin, aim+((u-0.5)*horizontal + (v-0.5)*vertical) - origin);
    }
    camera(vec3<> origin_, 
          vec3<> aim_, 
          vec3<> up_,
          double width,
          double height) : aim(aim_),
                        origin(0,0,0),
                        horizontal(width*unit_vector(cross(aim,up_))),
                        vertical(height*unit_vector(cross(horizontal,aim))){}
};
