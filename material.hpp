#pragma once
#include "hitable.hpp"
#include "rng.hpp"

class material{
  public:
    typedef std::shared_ptr<material> Ptr;
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const = 0;
};

class lambert : public material {
  private:
    vec3 albedo;
  public:
    lambert(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const {
        vec3 target = rec.p + rec.normal + rng::random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
};

inline vec3 reflect(const vec3& v, const vec3& n){
    return v - 2*dot(v,n)*n;
}

class metal : public material {
  private:
    vec3 albedo;
    float fuzz;
  public:
    metal(const vec3& a, double f) : albedo(a), fuzz(f) {}
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*rng::random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};