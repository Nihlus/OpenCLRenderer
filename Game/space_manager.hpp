#ifndef SPACE_MANAGER_H_INCLUDED
#define SPACE_MANAGER_H_INCLUDED

#include <GL/glew.h>

#include <boost/compute/source.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/iota.hpp>
#include <boost/compute/interop/opengl.hpp>

#include "../clstate.h"
#include "../point_cloud.hpp"

struct object_context_data;

namespace compute = boost::compute;

struct space_manager
{
    bool distortion_set;

    compute::buffer g_space_depth; ///for us
    compute::buffer g_colour_blend;

    cl_float4 c_rot;
    cl_float4 c_pos;

    compute::opengl_renderbuffer* g_screen;
    compute::buffer* depth_buffer; ///regular rendering depth buffer
    compute::buffer* g_distortion_buffer;

    int width, height;

    void init(int _width, int _height);

    void update_camera(cl_float4 _c_pos, cl_float4 _c_rot);

    void set_screen(compute::opengl_renderbuffer&);
    void set_depth_buffer(compute::buffer&);
    void set_distortion_buffer(compute::buffer&);

    void draw_galaxy_cloud(point_cloud_info&, compute::buffer& g_pos);
    void draw_galaxy_cloud_modern(point_cloud_info& pc, cl_float4 camera_pos);

    void draw_space_dust_cloud(point_cloud_info&, compute::buffer& g_pos); ///separation of church and state?
    void draw_space_dust_no_tile(point_cloud_info&, compute::buffer& offset_pos); ///separation of church and state?
    void draw_space_nebulae(point_cloud_info&, compute::buffer& g_pos); ///separation of church and state?

    compute::event blit_space_to_screen(object_context_data& dat);
    compute::event clear_buffers();
};

#endif // SPACE_MANAGER_H_INCLUDED
