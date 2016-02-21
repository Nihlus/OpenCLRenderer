#ifndef INCLUDED_HPP_TEXTURE
#define INCLUDED_HPP_TEXTURE

#include <gl/glew.h>
#include <sfml/graphics.hpp>
#include <cl/cl.h>
#include <vector>
#include "obj_g_descriptor.hpp"
#include <functional>

const static cl_uint max_tex_size=2048;

struct texture;

void texture_load(texture*);
void texture_make_blank(texture* tex, int w, int h, sf::Color col);

struct texture_gpu;
struct texture_context_data;

struct texture
{
    sf::Image c_image;

    sf::Image mipmaps[MIP_LEVELS];
    ///location is unique string that is texture location, used to check if textures refer to the same thing

    bool is_active;
    bool is_loaded;
    bool is_unique; ///ie don't cache me

    bool has_mipmaps;

    bool cacheable;

    int id;

    int type;

    cl_uint gpu_id;

    std::string texture_location;

    cl_uint get_largest_num(int) const;

    sf::Image& get_texture_level(int);

    void set_texture_location(const std::string&);
    void set_location(const std::string&);
    void set_create_colour(sf::Color col, int w, int h);

    bool exists();

    cl_uint get_active_id();

    void push();

    void generate_mipmaps();
    void update_gpu_mipmaps(texture_context_data& gpu_dat);

    void activate();
    void inactivate();

    void set_unique();

    void load();

    texture();

    void update_me_to_gpu(texture_context_data& gpu_dat);
    void update_gpu_texture(const sf::Texture& tex, texture_context_data& gpu_dat, cl_int flip = true);
    void update_gpu_texture_col(cl_float4 col, texture_context_data& gpu_dat);
    void update_random_lines(cl_int num, cl_float4 col, cl_float2 pos, cl_float2 dir, texture_context_data& gpu_dat);

    cl_uint get_largest_dimension() const;

    void set_load_func(std::function<void (texture*)>);
    std::function<void (texture*)> fp;
};



#endif
