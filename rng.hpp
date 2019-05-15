#pragma once
#include <random>
#include "vec3.hpp"

class rng {

  private:
    std::random_device dev;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;
    rng() : dev(), gen(dev()), dist(0,1) {};
    rng(const rng&){};
    rng& operator=(const rng&) = delete;
    static rng* m_inst;

  public:
    static rng* inst();
    static double gen01();
    static vec3 random_in_unit_sphere();
    static vec3 random_in_unit_disk();
};