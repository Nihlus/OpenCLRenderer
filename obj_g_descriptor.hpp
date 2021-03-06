#ifndef INCLUDED_H_OBJ_G_DESCRIPTOR
#define INCLUDED_H_OBJ_G_DESCRIPTOR

#include <CL/cl.h>

#define MIP_LEVELS 4

///this is gpu side
struct obj_g_descriptor
{
    cl_float4 world_pos; ///w is blank
    cl_float4 world_rot; ///w is blank
    cl_float4 world_rot_quat;

    cl_float4 old_world_pos_1;
    cl_float4 old_world_pos_2;
    cl_float4 old_world_rot_quat_1;
    cl_float4 old_world_rot_quat_2;

    cl_float scale;
    cl_uint tid; ///texture id
    cl_uint rid;
    cl_uint mip_start;
    cl_uint has_bump;
    cl_float specular;
    cl_float spec_mult;
    cl_float diffuse;
    cl_uint two_sided;
    cl_int buffer_offset;
    ///add in a type here for shaders?
};

#endif // INCLUDED_H_OBJ_G_DESCRIPTOR
