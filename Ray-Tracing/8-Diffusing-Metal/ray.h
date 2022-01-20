// ray.h
// Colors in ray tracers are based on rays- think about how colors seem
//      more vivid up close versus far away. Rays are how you calculate 
//      that gradient. 
// A ray has an endpoint and a direction. So our ray class has an endpoint
//      and a direction!

# ifndef RAY_H
# define RAY_H

# include "vec3.h"

class ray {
    public:
        // Constructor

        // This syntax was a little unfamiliar to me- it's essentially just doing 
        //      this.orig = origin;
        //      this.dir = direction;
        //      this.tm = 0;
        // It goes ahead and maps the instance's arguments to fields.
        ray() {}
        ray( const point3& origin, const vec3& direction )
            : orig(origin), dir(direction), tm(0)
        {}

        ray( const point3& origin, const vec3& direction, double time )
            : orig(origin), dir(direction), tm(time)
        {}

        // Uses the 3D vector aliases to record where the origin point
        //      of a ray is and what direction it's going in. 
        point3 origin() const  { return orig; }
        vec3 direction() const { return dir; }
        double time() const    { return tm; }

        // Calculates what the value of the ray is at a given point 
        point3 at( double t ) const {
            return orig + t * dir;
        }

    public:
        point3 orig;
        vec3 dir;
        double tm;
};

#endif