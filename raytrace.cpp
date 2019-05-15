#include <iostream>
#include "vec3.hpp"

int main() {
    int nx = 200;
    int ny = 200;
    std::cout << "P3" << std::endl;
    std::cout << nx << " " << ny << std::endl;
    std::cout << "255" << std::endl;

    for(int j = ny-1; j >= 0; j--){
        for(int i = 0; i < nx; i++){
            vec3<double> col((double)i/nx,
                             (double)j/ny,
                             0.5);

            int ir = int(255.99*col.r());
            int ig = int(255.99*col.g());
            int ib = int(255.99*col.b());

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}