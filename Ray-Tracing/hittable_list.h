// hittable_list.h 
// Essentially just a list of all the hittables in the image. 

# ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "rtweekend.h"

# include "hittable.h"

# include <memory>
# include <vector>


class hittable_list : public hittable  {
    public:

        // Constructor
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        // Destructor
        void clear() { objects.clear(); }

        // Adds a new hittable to the list
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        // Calculates a hit or not
        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    // The items in the list 
    public:
        std::vector<shared_ptr<hittable>> objects;
};


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    auto hit_anything = false;
    auto closest_so_far = t_max;

    // Checks if an item in our list of hittables was struck by a ray, and records it
    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}


# endif