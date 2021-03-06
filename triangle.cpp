#include "triangle.hpp"

#include <vec/vec.hpp>

std::array<cl_float4, 6> quad::decompose()
{
    std::vector<vec3f> points;

    points.push_back(xyz_to_vec(p1));
    points.push_back(xyz_to_vec(p2));
    points.push_back(xyz_to_vec(p3));
    points.push_back(xyz_to_vec(p4));

    vec3f avg = {0.f,0.f,0.f};

    for(auto& i : points)
    {
        avg += i;
    }

    avg = avg / (float)points.size();

    auto sorted = sort_anticlockwise(points, avg);

    cl_float4 conv[4];

    for(int i=0; i<4; i++)
    {
        conv[i] = {sorted[i].v[0], sorted[i].v[1], sorted[i].v[2]};
    }

    ///sorted anticlockwise, now return both halves
    //return {conv[0], conv[2], conv[1], conv[1], conv[2], conv[3]};
    return {conv[0], conv[2], conv[1], conv[0], conv[3], conv[2]};
}
