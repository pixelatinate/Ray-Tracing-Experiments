// hittable.h
// A "hittable" is an abstract class for anything that is hit by a ray. This includes
//      our spheres!

# ifndef HITTABLE_H
# define HITTABLE_H

# include "rtweekend.h"

class material;

struct hit_record {
    // Take with a grain of salt...
    //      "p" refers to a point along the ray at distance "t",
    //      which is why it's recorded as a point3, or a location 
    //      in stored as a 3D vector.
    //      "normal" just means perpendicular to a reference surface. 
    //      In this case, I think it means the ray that's perpendicular 
    //      to the camera lens. 
    //          
    // If this doesn't make sense, refer to this paper (the pictures help!)
    //      https://link.springer.com/content/pdf/10.1007%2F978-1-4842-4427-2_2.pdf
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    // This determines the normal direction of a ray, considering things like material. 
    // Glass, for instance, is transparent, and therefore a ray will pass through it 
    //      instead of just bouncing straight off. "front_face" determines which face
    //      of a hittable is perpendicular to the ray coming out from behind the camera. 
    //      We call that "normal", and then set "-outword_normal" to be the opposite.
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

// Establishes the conditions for if a ray hits a sphere, and then defaults it to "no".
class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


# endif