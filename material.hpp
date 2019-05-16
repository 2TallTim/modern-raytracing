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


class metal : public material {
  private:
    vec3 albedo;
    double fuzz;
  public:
    metal(const vec3& a, double f) : albedo(a), fuzz(f) {}
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const {
        vec3 reflected = ray::reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*rng::random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};


class dielectric : public material {
  private:
    double ref_idx;
  public:
    dielectric(double ri) : ref_idx(ri) {}
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const {
        vec3 outward_normal;
        vec3 reflected = ray::reflect(unit_vector(r_in.direction()), rec.normal);
        double ni_over_nt;
        attenuation = vec3(1,1,1);
        vec3 refracted;
        double reflect_prob;
        double cosine;
        if( dot(r_in.direction(), rec.normal) > 0){
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }else{
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        if(ray::refract(r_in.direction(), outward_normal, ni_over_nt, refracted)){
            reflect_prob = ray::schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        }
        if(rng::gen01()< reflect_prob){
            scattered = ray(rec.p, reflected);
        }else{
            scattered = ray(rec.p, refracted);
        }
        
        return true;
    }
};