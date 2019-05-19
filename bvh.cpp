#include "bvh.hpp"

bool bvh_node::bounding_box(aabb& b) const{
    b = box;
    return true;
}

bool bvh_node::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    if(box.hit(r,t_min,t_max)){
        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r,t_min,t_max,left_rec);
        bool hit_right = right->hit(r,t_min,t_max,right_rec);
        if(hit_left && hit_right){
            rec = left_rec.t < right_rec.t ? left_rec : right_rec;
            return true;
        } else if(hit_left) {
            rec = left_rec;
            return true;
        } else if(hit_right) {
            rec = right_rec;
            return true;
        }
    }
    return false;
}

template<int axis>
struct box_compare {
    inline bool operator() (const hitable::Ptr& a, const hitable::Ptr& b){
        aabb box_left, box_right;
        if(!a->bounding_box(box_left) || !b->bounding_box(box_right))
            std::cerr << "no bounding box in bvh_node constructor!" << std::endl;
        return box_left.min()[axis] < box_right.min()[axis];
    }
};

bvh_node::bvh_node(std::vector<hitable::Ptr>::iterator begin,
                   std::vector<hitable::Ptr>::iterator end) {
    int axis = int(rng::gen01()*3);
    switch (axis)
    {
    case 0:
        std::sort(begin,end,box_compare<0>());
        break;
    case 1:
        std::sort(begin,end,box_compare<1>());
        break;
    case 2:
        std::sort(begin,end,box_compare<2>());
    default:
        break;
    }
    int dist = std::distance(begin,end);
    if(dist == 1){
        left = right = *begin;
    }else if(dist == 2){
        left = *begin;
        right = *(begin+1);
    }else{
        left = std::make_shared<bvh_node>(begin,begin+dist/2);
        right = std::make_shared<bvh_node>(begin+dist/2,end);
    }

    aabb box_left, box_right;
    if(!left->bounding_box(box_left) || !right->bounding_box(box_right))
        std::cerr << "no bounding box in bvh_node constructor!" << std::endl;
    box = aabb::surrounding_box(box_left,box_right);
}