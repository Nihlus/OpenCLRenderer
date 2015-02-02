#include "clstate.h"

///kernel information and opencl stuff

compute::device cl::device;
compute::command_queue cl::cqueue;
compute::context cl::context;


kernel cl::kernel1;
kernel cl::kernel2;
kernel cl::kernel3;
kernel cl::prearrange;
kernel cl::kernel1_oculus;
kernel cl::kernel2_oculus;
kernel cl::kernel3_oculus;
kernel cl::prearrange_oculus;
kernel cl::point_cloud_depth;
kernel cl::point_cloud_recover;
kernel cl::space_dust;
kernel cl::space_dust_no_tile;
kernel cl::draw_ui;
kernel cl::draw_hologram;
kernel cl::blit_with_id;
kernel cl::blit_clear;
kernel cl::clear_id_buf;
kernel cl::clear_screen_dbuf;
kernel cl::draw_voxel_octree;
kernel cl::create_distortion_offset;
kernel cl::draw_fancy_projectile;
kernel cl::reproject_depth;
kernel cl::reproject_screen;
kernel cl::space_nebulae;
kernel cl::edge_smoothing;
kernel cl::shadowmap_smoothing_x;
kernel cl::shadowmap_smoothing_y;
kernel cl::raytrace;
kernel cl::render_voxels;
kernel cl::render_voxels_tex;
kernel cl::render_voxel_cube;
kernel cl::diffuse_unstable;
kernel cl::diffuse_unstable_tex;
kernel cl::advect;
kernel cl::advect_tex;
kernel cl::post_upscale;
kernel cl::warp_oculus;
kernel cl::goo_diffuse;
kernel cl::goo_advect;
kernel cl::fluid_amount;
kernel cl::update_boundary;
kernel cl::fluid_initialise_mem;
kernel cl::fluid_timestep;

