#ifndef INCLUDED_HPP_PROJ
#define INCLUDED_HPP_PROJ

#include <cstdio>
#include <string>
#include <iostream>

#include <GL/glew.h>

//#include <windows.h>

#include <GL/gl.h>
#include <GL/glext.h>


#include <CL/cl.h>

/*#ifndef CL_USE_DEPRECATED_OPENCL_1_1_APIS
static cl_mem fake;
#define clCreateFromGLTexture2D(...) fake
#endif*/

#include "texture.hpp"
#include "clstate.h"
#include "obj_load.hpp"
#include "objects_container.hpp"
#include "engine.hpp"
#include "obj_g_descriptor.hpp"
#include <math.h>
#include <limits.h>

#include <boost/compute/system.hpp>

namespace compute = boost::compute;

template<typename T>
std::string to_str(T i)
{
    std::ostringstream convert;

    convert << i;

    return convert.str();
}

#endif
