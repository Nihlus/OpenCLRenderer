cmake_minimum_required(VERSION 3.6)
project(pfix)

set(pfix_VERSION_MAJOR 1)
set(pfix_VERSION_MINOR 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-std=gnu++14 -Wno-c++11-narrowing -fexceptions -DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(OpenGL)
find_package(OpenCL)
find_package(GLEW)
find_package(Threads)
find_package(SFML 2 REQUIRED system window graphics)

set(PFIX_SOURCES
		${PROJECT_SOURCE_DIR}/clstate.cpp
		${PROJECT_SOURCE_DIR}/controls.cpp
		${PROJECT_SOURCE_DIR}/engine.cpp
		${PROJECT_SOURCE_DIR}/hologram.cpp
		${PROJECT_SOURCE_DIR}/interact_manager.cpp
		${PROJECT_SOURCE_DIR}/light.cpp
		${PROJECT_SOURCE_DIR}/logging.cpp
		${PROJECT_SOURCE_DIR}/main.cpp
		${PROJECT_SOURCE_DIR}/obj_info_struct.cpp
		${PROJECT_SOURCE_DIR}/obj_load.cpp
		${PROJECT_SOURCE_DIR}/object.cpp
		${PROJECT_SOURCE_DIR}/object_context.cpp
		${PROJECT_SOURCE_DIR}/objects_container.cpp
		${PROJECT_SOURCE_DIR}/ocl.cpp
		${PROJECT_SOURCE_DIR}/point_cloud.cpp
		${PROJECT_SOURCE_DIR}/text_handler.cpp
		${PROJECT_SOURCE_DIR}/texture.cpp
		${PROJECT_SOURCE_DIR}/texture_context.cpp
		${PROJECT_SOURCE_DIR}/triangle.cpp
		${PROJECT_SOURCE_DIR}/ui_manager.cpp
		${PROJECT_SOURCE_DIR}/vertex.cpp)

set(PFIX_HEADERS
		${PROJECT_SOURCE_DIR}/clstate.h
		${PROJECT_SOURCE_DIR}/controls.hpp
		${PROJECT_SOURCE_DIR}/engine.hpp
		${PROJECT_SOURCE_DIR}/hologram.hpp
		${PROJECT_SOURCE_DIR}/interact_manager.hpp
		${PROJECT_SOURCE_DIR}/light.hpp
		${PROJECT_SOURCE_DIR}/logging.hpp
		${PROJECT_SOURCE_DIR}/obj_g_descriptor.hpp
		${PROJECT_SOURCE_DIR}/obj_info_struct.hpp
		${PROJECT_SOURCE_DIR}/obj_load.hpp
		${PROJECT_SOURCE_DIR}/object.hpp
		${PROJECT_SOURCE_DIR}/object_context.hpp
		${PROJECT_SOURCE_DIR}/objects_container.hpp
		${PROJECT_SOURCE_DIR}/ocl.h
		${PROJECT_SOURCE_DIR}/point_cloud.hpp
		${PROJECT_SOURCE_DIR}/proj.hpp
		${PROJECT_SOURCE_DIR}/text_handler.hpp
		${PROJECT_SOURCE_DIR}/texture.hpp
		${PROJECT_SOURCE_DIR}/texture_context.hpp
		${PROJECT_SOURCE_DIR}/triangle.hpp
		${PROJECT_SOURCE_DIR}/ui_manager.hpp
		${PROJECT_SOURCE_DIR}/vec.hpp
		${PROJECT_SOURCE_DIR}/vertex.hpp)

include_directories(
		${OPENGL_INCLUDE_DIR}
		${OpenCL_INCLUDE_DIR}
		${SFML_INCLUDE_DIR}
		${PROJECT_SOURCE_DIR}/../libraries
		${PROJECT_SOURCE_DIR}/../libraries/half
		${PROJECT_SOURCE_DIR}/../libraries/compute/include)

add_executable(pfix ${PFIX_SOURCES} ${PFIX_HEADERS})

target_link_libraries(
		${PROJECT_NAME}
		${OPENGL_gl_LIBRARY}
		${OpenCL_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT}
		${SFML_LIBRARIES})

file(COPY ${PROJECT_SOURCE_DIR}/cl2.cl DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})