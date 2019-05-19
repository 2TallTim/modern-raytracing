#include "hitable_list.hpp"

bool hitable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (auto ht : list){
        if (ht->hit(r,t_min,closest_so_far,temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

void hitable_list::add(const hitable::Ptr& p){
    list.push_back(p);
}

bool hitable_list::bounding_box(aabb& box){
    if(list.size() < 1) return false;
    aabb temp_box;
    bool first_true = list.front()->bounding_box(temp_box);
    if(!first_true)
        return false;
    else
        box = temp_box;
    
    for(auto iter = ++(list.begin()); iter != list.end(); iter++){
        if((*iter)->bounding_box(temp_box))
            box = aabb::surrounding_box(box,temp_box);
        else
            return false;
    } 

}