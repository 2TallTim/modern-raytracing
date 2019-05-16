#pragma once

#include "ray.hpp"

class camera{
private:
    double lens_radius;
    vec3 aim;
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 u,v,w;
public:
    ray get_ray(double s, double t){
        vec3 rd = lens_radius*rng::random_in_unit_disk();
        vec3 offset = u*rd.x() + v * rd.y();
        return ray(origin+offset, aim+((s-0.5)*horizontal + (t-0.5)*vertical) - origin - offset);
    }
    camera(vec3 origin_, vec3 aim_, vec3 up_,
           double vfov, double aspect, double aperture, double focus_dist) {
        lens_radius = aperture / 2;
        double theta = vfov*M_PI/180;
        double half_height = tan(theta/2);
        double half_width = aspect*half_height;
        origin = origin_;
        w = unit_vector(origin_ - aim_);
        u = unit_vector(cross(up_, w));
        v = cross(w,u);
        horizontal = 2*half_width*focus_dist*u;
        vertical = 2*half_height*focus_dist*v;
    }
};
