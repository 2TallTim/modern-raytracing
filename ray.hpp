#pragma once

#include "vec3.hpp"

class ray{
  public:
    ray(const vec3<>& a, const vec3<>& b) : O(a), D(b) {}
    vec3<> origin() const { return O; }
    vec3<> direction() const { return D; }
    vec3<> point_at_parameter(double t) const { return O + t*D; }

  private:
    vec3<> O; // Ray origin
    vec3<> D; // Ray direction
};