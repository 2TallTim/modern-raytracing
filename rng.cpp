#include "rng.hpp"
rng* rng::m_inst = NULL;

rng* rng::inst(){
    if(!m_inst)
        m_inst = new rng();
    
    return m_inst;
}

double rng::gen01(){
    return inst()->dist(inst()->gen);
}

vec3 rng::random_in_unit_sphere(){
    vec3 p;
    do {
        p = 2.0 * vec3(gen01(), gen01(), gen01()) - vec3(1, 1, 1);
    } while(p.squared_length() >= 1.0);
    return p;
}

vec3 rng::random_in_unit_disk(){
    vec3 p;
    do {
        p = 2.0 * vec3(gen01(),gen01(),0) - vec3(1,1,0);
    } while(p.squared_length() >= 1.0);
    return p;
}