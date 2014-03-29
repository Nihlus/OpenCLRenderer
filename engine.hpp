#ifndef INCLUDED_HPP_ENGINE
#define INCLUDED_HPP_ENGINE
#include <SFML/graphics.hpp>
#include "object.hpp"
#include <vector>
#include "objects_container.hpp"
#include "light.hpp"
#include "clstate.h"

#include <boost/compute/source.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/iota.hpp>
#include <boost/compute/interop/opengl.hpp>

namespace compute = boost::compute;

struct engine
{
    sf::Mouse mouse;

    cl_uint width, height, depth;
    cl_uint g_size; /// height > width rounded up to nearest power of 2
    cl_uint l_size;
    cl_float4 c_pos;
    cl_float4 c_rot;

    compute::opengl_renderbuffer g_screen;

    compute::buffer g_c_pos;
    compute::buffer g_c_rot;

    compute::buffer depth_buffer[2]; ///switches between the two every frame ///make this a 2d image?
    //cl_mem g_depth_screen;
    compute::buffer g_id_screen;
    compute::image2d g_id_screen_tex;
    compute::buffer g_normals_screen;
    compute::buffer g_texture_screen;
    compute::buffer g_shadow_light_buffer;
    compute::buffer g_shadow_occlusion_screen;

    compute::buffer g_tid_buf;
    compute::buffer g_tid_buf_max_len;
    compute::buffer g_tid_buf_atomic_count;
    int c_tid_buf_len;

    compute::buffer g_valid_fragment_mem;
    compute::buffer g_valid_fragment_num;

    cl_uint* d_depth_buf;
    compute::buffer d_triangle_buf;
    triangle *dc_triangle_buf;

    static unsigned int gl_screen_id;
    static unsigned int gl_framebuffer_id;

    cl_uint *blank_light_buf;
    cl_uint shadow_light_num;

    sf::RenderWindow window;

    std::vector<object*> objects;

    void load(cl_uint, cl_uint, cl_uint, std::string);

    int add_light(light&);
    void set_light_pos(int, cl_float4);
    void g_flush_lights(); ///not implemented
    void g_flush_light(int);
    void realloc_light_gmem();

    void construct_shadowmaps();
    void draw_bulk_objs_n();
    void render_buffers();

    void input();
    int get_mouse_x();
    int get_mouse_y();

    void set_camera_pos(cl_float4);
    void set_camera_rot(cl_float4);

    void check_obj_visibility();
};


static void run_kernel_with_args(compute::kernel &kernel, cl_uint *global_ws, cl_uint *local_ws, int dimensions, compute::buffer **argv, int argc, bool blocking)
{
    for(int i=0; i<argc; i++)
    {
        kernel.set_arg(i, *(argv[i]));
    }

    cl::cqueue.enqueue_nd_range_kernel(kernel, dimensions, NULL, global_ws, local_ws);


    if(blocking)
        cl::cqueue.finish();
}


#endif
