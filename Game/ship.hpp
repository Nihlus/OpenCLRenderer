#ifndef INCLUDED_SHIP_HPP
#define INCLUDED_SHIP_HPP
#include <cl/cl.h>
#include <math.h>
#include "../objects_container.hpp"
#include "../light.hpp"

#define MAX_ANGULAR 1.0f

/*static cl_float4 slerp(cl_float4 p0, cl_float4 p1, float t)
{
    float angle = p0.x*p1.x + p0.y*p1.y + p0.z*p1.z;

    cl_float4 interp;

    float ix = (sin((1.0f - t)*angle)/sin(angle)) * p0.x + (sin(t*angle)/sin(angle))*p1.x;
    float iy = (sin((1.0f - t)*angle)/sin(angle)) * p0.y + (sin(t*angle)/sin(angle))*p1.y;
    float iz = (sin((1.0f - t)*angle)/sin(angle)) * p0.z + (sin(t*angle)/sin(angle))*p1.z;

    interp.x = ix;
    interp.y = iy;
    interp.z = iz;
    interp.w = 0.0f;

    return interp;
}*/

struct newtonian_body;

struct newtonian_manager
{
    static std::vector<newtonian_body*> body_list;

    static void add_body(newtonian_body*);
    static void remove_body(newtonian_body*);

    static void tick_all(float);
};

struct newtonian_body
{
    int type; ///0 is regular object, 1 is laser

    //int lid;

    cl_float4 position;
    cl_float4 rotation;

    cl_float4 linear_momentum;
    cl_float4 rotational_momentum;

    cl_float4 attempted_rotation_direction;
    cl_float4 attempted_force_direction;

    objects_container* obj;
    light* laser;

    float mass;

    float thruster_force; ///of all thrusters
    float thruster_distance; ///of all thrusters

    float thruster_forward;

    virtual void tick(float);

    virtual void set_rotation_direction(cl_float4 _dest);
    virtual void set_linear_force_direction(cl_float4 _dir);

    newtonian_body* push();
    newtonian_body* push_laser(light*);

    newtonian_body();

    virtual void fire();

    virtual newtonian_body* clone();

    //std::vector<cl_float4> thrusters_pos;
    //std::vector<cl_float4> thrusters_force;
};

struct ship : newtonian_body
{
    ///put weapon in here
    void fire();

    ship* clone();

    newtonian_body* push();
};

struct projectile : newtonian_body
{

};


#endif // INCLUDED_SHIP_HPP
