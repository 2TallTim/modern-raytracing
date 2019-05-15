#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"

typedef vec3<> vec;

vec color(const ray& r, hitable::Ptr world) {
    hit_record rec;
    if(world->hit(r,0.0,MAXFLOAT,rec)){
        return 0.5 * (rec.normal + vec(1,1,1));
    } else {
        vec unit_direction = unit_vector(r.direction());
        double t = 0.5 *(unit_direction.y() + 1.0);
        return (1.0-t) * vec(1.0, 1.0, 1.0) + t*vec(0.5,0.7,1.0);
    }
}

int main() {


    int nx = 200;
    int ny = 100;
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;

    vec lower_left_corner(-2, -1, -1);
    vec horizontal(4,0,0);
    vec vertical(0,2,0);
    vec origin(0,0,0);

    std::shared_ptr<hitable_list> world = std::make_shared<hitable_list>();
    world->add(std::make_shared<sphere>(vec(0,0,-1), 0.5) );
    world->add(std::make_shared<sphere>(vec(0,-100.5,-1), 100));


    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            double u = (double)i/nx;
            double v = (double)j/ny;

            ray r(origin, lower_left_corner + u*horizontal+v*vertical);
            vec col = color(r,world);

            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}