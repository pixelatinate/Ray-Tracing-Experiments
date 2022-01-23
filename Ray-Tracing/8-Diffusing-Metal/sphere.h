// sphere.h
// This file contains all the information for what a sphere will look like. 
//      This includes the center of the circle, stored in the 3D vector class,
//      the length of the radius, and which material the sphere should use. 

#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"

#include "hittable.h"


class sphere : public hittable {
    public:
        // Constructor 

        sphere() {}
        sphere(point3 cen, double r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};


bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    
    // Google "spherical trigonometry" for more information on what OC is. 
    //      Essentially, OC goes from the center of the circle to the outer edge. 
    // Uppercase A, B, and C in spherical trig refer to points on the outside of 
    //      a circle. Lowercase a, b, and c refer to the distance between uppercase
    //      A, B, and C.
    // In the cases below, we're referring to lowercase a, b, and c. This code
    //      calculates where rays intersect with the sphere. 
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    // The discriminant is a staple in matrix algebra. It's essentially the inverse
    //      of a matrix. 
    auto discriminant = half_b*half_b - a*c;


    if (discriminant < 0){
        return false;
    } 
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif