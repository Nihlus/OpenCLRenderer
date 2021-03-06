#ifndef TEXTURE_CONTEXT_HPP_INCLUDED
#define TEXTURE_CONTEXT_HPP_INCLUDED

#include <vector>
#include <CL/cl.h>

#include <GL/glew.h>

#include <boost/compute/source.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/iota.hpp>
#include <boost/compute/interop/opengl.hpp>

#define TEXTURE_CONTEXT_MAX_SIZE_IMAGE 2048
#define TEXTURE_CONTEXT_MIP_LEVELS 4

struct object_context;
struct texture;

namespace compute = boost::compute;

typedef int texture_id_t;
//typedef unsigned int texture_id_t;

struct texture_context_data
{
    compute::buffer g_texture_sizes;
    compute::buffer g_texture_nums; ///cant be arsed to rename every single instance of this

    ///either an image3d OR a uint4 buffer depending on hardware support
    compute::buffer g_texture_array;
    cl_uint mipmap_start;
};

struct texture_context
{
    std::vector<texture*> all_textures;
    std::vector<texture_id_t> texture_id_orders;

    std::set<texture_id_t> last_build_textures;

    texture* make_new();
    texture* make_new_cached(const std::string& loc);

    void destroy(texture* tex);

    int mipmap_start;

    ///scrap the concept of active textures
    ///simply pass objects with their associated texture ids?

    texture_context_data alloc_gpu(object_context& ctx);

    texture* id_to_tex(int);

    int gid = 0;

    bool should_realloc(object_context&);

    int get_gpu_position_id(texture_id_t id);
};


#endif // TEXTURE_CONTEXT_HPP_INCLUDED
