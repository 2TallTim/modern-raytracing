#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "rng.hpp"
#include "material.hpp"
#include <random>


vec3 color(const ray& r, hitable::Ptr world, int depth=0) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation * color(scattered, world, depth+1);
        }else{
            return vec3(0,0,0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 *(unit_direction.y() + 1.0);
        return (1.0-t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5,0.7,1.0);
    }
}

int main() {
    const int nx = 200;
    const int ny = 100;
    const int ns = 100;

    

    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;

    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    vec3 origin(0,0,0);

    std::shared_ptr<hitable_list> world = std::make_shared<hitable_list>();

    material::Ptr mat = std::make_shared<lambert>(vec3(0.1,0.2,0.5));
    hitable::Ptr sp = std::make_shared<sphere>(vec3(0,0,-1), 0.5, mat);
    world->add(sp);

    mat = std::make_shared<lambert>(vec3(0.8,0.8,0));
    sp = std::make_shared<sphere>(vec3(0,-100.5,-1), 100, mat);
    world->add(sp);

    mat = std::make_shared<metal>(vec3(0.8,0.6,0.2), 0.0);
    sp = std::make_shared<sphere>(vec3(1,0,-1), 0.5, mat);
    world->add(sp);

    mat = std::make_shared<dielectric>(1.5);
    sp = std::make_shared<sphere>(vec3(-1,0,-1), 0.5, mat);
    world->add(sp);
    
    camera cam(origin, vec3(0,0,-1), vec3(0,1,0), 4, 2);

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3 col(0,0,0);

            for (int s = 0; s < ns; s++){
                double u = (double)(i+rng::gen01())/nx;
                double v = (double)(j+rng::gen01())/ny;
                ray r = cam.get_ray(u, v);

                col+= color(r, world); 
            }
            col /= (double)ns;
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}