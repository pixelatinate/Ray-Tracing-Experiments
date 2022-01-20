// vec3.h
// This file contains all the information for a 3D vector class. 
//      We'll use this vector to contain the data about colors, 
//      locations, offsets, and directions of our hittables. 

// We declare two aliases for vec3: point3 and color. Remember- 
//      because vec3 is essentially a 3D vector (i.e., a flexible
//      class we can use for a lot of different things), we use 
//      the alias "point3" to describe where the hittable is in the 
//      space, and "color" to describe the rgb makeup of the hittable!

// This means that if you're not careful, you can accidentally
//      pass a color to a function when it's asking for a location, 
//      so keep an eye out for that. 

# ifndef VEC3_H
# define VEC3_H

# include <cmath>
# include <iostream>

using namespace std;

class vec3 {
    public:
        // Constructor 
        vec3() : e{ 0, 0, 0 } {}
        vec3( double e0, double e1, double e2 ) : e{ e0, e1, e2 } {}

        // If a function asks for x, y, or z, return the first, second,
        //      or third argument
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // If a function asks for the negative of an argument, we define 
        //      the negative behavior here, along with the behavior for 
        //      any "i" argument or the reference to an "i" argument. 
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Allows you to perform addition on an argument without 
        //      augmenting the actual value through use of references
        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        // Allows you to perform multiplication on an argument without 
        //      augmenting the actual value through use of references
        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        // Allows you to perform division on an argument without 
        //      augmenting the actual value through use of references
        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        // Allows you to calculate the length of a hittable
        double length() const {
            return sqrt( length_squared() );
        }

        // Allows you to calculate the length squared of a hittable
        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        // Tells us if we're super close to zero- this is useful for
        //      things like clearing up "shadow acne". Returns true 
        //      if the vector is close to zero in all dimensions.
        bool near_zero() const {
            const auto s = 1e-8;
            return ( fabs(e[0]) < s ) && ( fabs( e[1] ) < s ) && ( fabs( e[2] ) < s );
        }

        // Returns a random value as the vector values
        inline static vec3 random() {
            return vec3( random_double(), random_double(), random_double() );
        }

        // Returns a random value within supplied parameters as the the vector values
        inline static vec3 random( double min, double max ) {
            return vec3( random_double( min, max ), random_double( min, max ), random_double( min, max ) );
        }

    public:
        double e[3];
};


// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color


// vec3 Utility Functions
// For use when calculating linear algebra stuff- if confused, refer to 
//      the descriptions of similar functions above. 
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

# endif