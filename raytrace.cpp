#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <sstream>
#include <atomic>
#include <fstream>
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "rng.hpp"
#include "material.hpp"

vec3 color(const ray& r, hitable::Ptr world, int depth=0) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if (depth < 10 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
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

int main(int argc, char** argv) {
    const int nx = 600;
    const int ny = 300;
    const int ns = 100;
    const int nobj = 500;
    const double tgt_var = 0.05;


    std::shared_ptr<hitable_list> world = std::make_shared<hitable_list>();

    for(int a = -11; a<11; a++){
        for(int b = -11; b<11; b++){
            double choose_mat = rng::gen01();
            vec3 center(a+0.9*rng::gen01(), 0.2, b+0.9*rng::gen01());
            if((center-vec3(4,0.2,0)).squared_length() > 0.8){
                material::Ptr mat;
                if(choose_mat < 0.8){ //diffuse
                    mat = std::make_shared<lambert>(vec3(rng::gen01()*rng::gen01(),rng::gen01()*rng::gen01(),rng::gen01()*rng::gen01()));
                } else if (choose_mat < 0.95) { //metal 
                    mat = std::make_shared<metal>(vec3(0.5*(1+rng::gen01()), 0.5*(1+rng::gen01()),0.5*(1+rng::gen01())), 0.5 * rng::gen01());
                } else { //glass
                    mat = std::make_shared<dielectric>(1.5);
                }
                hitable::Ptr sp = std::make_shared<sphere>(center, 0.2, mat);
                world->add(sp);
            }
        }
        
    }

    material::Ptr mat = std::make_shared<lambert>(vec3(0.5,0.5,0.5));
    hitable::Ptr sp = std::make_shared<sphere>(vec3(0,-1000,0), 1000, mat);
    world->add(sp);

    mat = std::make_shared<dielectric>(1.5);
    sp = std::make_shared<sphere>(vec3(0,1,0), 1.0, mat);
    world->add(sp);
    
    mat = std::make_shared<lambert>(vec3(0.4,0.2,0.1));
    sp = std::make_shared<sphere>(vec3(-4, 1, 0), 1.0, mat);
    world->add(sp);
    
    mat = std::make_shared<metal>(vec3(0.7,0.6,0.5), 0.0);
    sp = std::make_shared<sphere>(vec3(4,1,0), 1.0, mat);
    world->add(sp);

    vec3 origin(12,1,3);
    vec3 aim(0,1,0);
    double dist_to_focus = (origin-aim).length();
    double aperture = 0.1;

    camera cam(origin, aim, vec3(0,1,0), 30,(double)nx/ny,aperture, dist_to_focus);

    std::mutex result_mutex;
    std::vector<std::string> results(ny);
    std::vector<std::string> smpmap(ny);
    std::atomic_int nextrow(-1);

    auto renderRow = [&]()->void{
        int j = ++nextrow;
        while(j < ny){
            std::stringstream tmpresults;
            std::stringstream smpcntresults;
            tmpresults << "# ROW " << j << std::endl;
            int t_samples = 0;
            for(int i = 0; i < nx; i++){
                vec3 col, vr;

                //Intialize variance tracking
                int s = 0;
                for (s = 0; s < ns; s++){
                    double u = (double)(i+rng::gen01())/nx;
                    double v = (double)(j+rng::gen01())/ny;
                    ray r = cam.get_ray(u, v);
                    vec3 sample = color(r, world);

                    t_samples++;

                    col += sample;

                    vr += vec3(sample.r()*sample.r(),
                               sample.g()*sample.g(),
                               sample.b()*sample.b());

                    if(s > sqrt((float)ns)){
                        vec3 musquared_s((col.r()*col.r())/s,
                                         (col.g()*col.g())/s,
                                         (col.b()*col.b())/s );
                        vec3 variance = ((double)s/((s-1) * (double)s)) * (vr-musquared_s);
                        variance = vec3(variance.r()*variance.r(),
                                        variance.g()*variance.g(),
                                        variance.b()*variance.b());
                        if((variance.r() < tgt_var) && 
                           (variance.g() < tgt_var) && 
                           (variance.b() < tgt_var)) break;
                }
                }
                col = col/(s+1);
                col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
                int ir = int(255.99*col.r());
                int ig = int(255.99*col.g());
                int ib = int(255.99*col.b());

                tmpresults << ir << " " << ig << " " << ib << std::endl;
                int nsgv = int((double)(255.9*s)/ns);
                smpcntresults << nsgv << " " << nsgv << " " << nsgv << std::endl;
            }
            std::lock_guard<std::mutex> lock(result_mutex);
            results[j] = tmpresults.str();
            smpmap[j] = smpcntresults.str();
            j = ++nextrow;
            std::cout << j << " / " << ny << " Avg samples in row: " << (double)t_samples/nx <<std::endl;
        }
    };
    std::vector<std::thread> threads;
    for(int t=0; t < std::thread::hardware_concurrency() - 1; t++){
        threads.push_back(std::thread(renderRow));
    }
    for(auto& t : threads ){
        t.join();
    }

    std::stringstream header;
    header << "P3" << std::endl;
    header << nx << " " << ny << std::endl;
    header << "255" << std::endl;
    
    results.push_back(header.str());
    smpmap.push_back(header.str());
    if(argc == 1){
        for(auto iter = results.rbegin(); iter != results.rend(); iter++){
            std::cout << *iter;
        }
    } else {
        std::ofstream out(argv[1],std::ios::out);
        for(auto iter = results.rbegin(); iter != results.rend(); iter++){
            out << *iter;
        }
    }
    std::ofstream smpout("./samples.ppm", std::ios::out);
    for(auto iter = smpmap.rbegin(); iter != smpmap.rend(); iter++){
        smpout << *iter;
    }
}