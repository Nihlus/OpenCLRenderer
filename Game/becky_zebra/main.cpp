#include "../../proj.hpp"
#include <map>

#include "../../Rift/Include/OVR.h"
#include "../../Rift/Include/OVR_Kernel.h"
//#include "Include/OVR_Math.h"
#include "../../Rift/Src/OVR_CAPI.h"
#include "../../vec.hpp"

/*struct zebra_info
{
    float angle;
    float x, y;
};*/

struct zebra
{
    //cl_float4 pos = {0,0,0,0};
    //cl_float angle = 0;

    static int bound;

    static std::map<objects_container*, float> angles;

    static std::vector<objects_container*> objects;

    static void add_object(objects_container* obj)
    {
        objects.push_back(obj);

        cl_float4 pos = obj->pos;

        pos.x = fmod(rand() - RAND_MAX/2,  bound);
        pos.z = fmod(rand() - RAND_MAX/2,  bound);

        obj->set_pos(pos);
    }

    static void separate()
    {
        /*int bound = 1000000000;

        bool success = false;

        std::cout << objects.size() << std::endl;

        while(!success)
        {
            bool tmp = true;

            for(int i=0; i<objects.size(); i++)
            {
                cl_float4 p1 = objects[i]->pos;

                for(int j=0; j<objects.size(); j++)
                {
                    cl_float4 p2 = objects[j]->pos;

                    float d1 = dist(p1, p2);

                    //printf("%f\n", d1);

                    if(d1 < 10)
                    {
                        //printf("ostrich\n\n\n\n\n\n\n\n\n\n");

                        tmp = false;

                        p2.x = fmod(rand() - RAND_MAX/2,  bound);
                        p2.z = fmod(rand() - RAND_MAX/2,  bound);

                        //printf("tits\n");

                        objects[j]->set_pos(p2);
                    }
                }
            }

            success = tmp;
        }*/

        int xgrid = sqrtf(objects.size());
        int ygrid = sqrtf(objects.size());

        for(int j=0; j<ygrid; j++)
        {
            for(int i=0; i<xgrid; i++)
            {
                int id = j*xgrid + i;

                id = std::min(id, (int)objects.size());

                cl_float4 pos = objects[id]->pos;

                float angle = fmod(rand(), M_PI*2);

                float xangle = 250*cos(angle);
                float yangle = 250*sin(angle);

                pos.x = i*1000 + xangle;// + fmod(ran d() - RAND_MAX/2, 250);
                pos.z = j*1000 + yangle;// + fmod(rand() - RAND_MAX/2, 250);

                objects[j*xgrid + i]->set_pos(pos);
            }
        }

        int max_id = (ygrid - 1)*xgrid + xgrid-1;

        for(int i=max_id; i<objects.size(); i++)
        {

            //objects[i].set_pos({})
        }
    }

    static void update(objects_container* zeb)
    {
        ///angle is in 2d plane

        cl_float4 pos = zeb->pos;
        cl_float rot = zeb->rot.y;//?

        float speed = 50.0f;

        //float new_angle = (fmod(rand(), 3.14159) + rot*70) / 71;

        if(angles[zeb] == 0)
        {
            angles[zeb] = fmod(rand(), 3.14159);
        }

        float new_angle = angles[zeb];

        //float new_angle = rot;

        float xdir, zdir;

        //xdir = speed*cos(new_angle);
        //zdir = speed*sin(new_angle);

        zdir = -speed;

        pos.x += xdir;
        pos.z += zdir;

        zeb->set_pos(pos);
        zeb->set_rot({zeb->rot.x, new_angle, zeb->rot.z});

        zeb->g_flush_objects();
    }
};

std::map<objects_container*, float> zebra::angles;

int zebra::bound = -3000;

std::vector<objects_container*> zebra::objects;

int main(int argc, char *argv[])
{
    ///remember to make g_arrange_mem run faster!

    constexpr int zebra_count = 3025;

    sf::Clock load_time;

    objects_container zebras[zebra_count];

    for(int i=0; i<zebra_count; i++)
    {
        zebras[i].set_file("tex_cube.obj");
        zebras[i].set_active(true);

        zebra::add_object(&zebras[i]);
    }

    engine window;

    window.load(1280,768,1000, "turtles", "../../cl2.cl");

    window.set_camera_pos((cl_float4){sqrt(zebra_count)*500,600,-570});
    window.c_rot.x = -M_PI/2;


    //window.window.setVerticalSyncEnabled(false);

    ///write a opencl kernel to generate mipmaps because it is ungodly slow?
    ///Or is this important because textures only get generated once, (potentially) in parallel on cpu?

    obj_mem_manager::load_active_objects();

    for(int i=0; i<zebra_count; i++)
        zebras[i].scale(200.0f);

    zebra::separate();

    texture_manager::allocate_textures();

    obj_mem_manager::g_arrange_mem();
    obj_mem_manager::g_changeover();

    //window.c_rot.z += 0.9;

    sf::Event Event;

    light l;
    l.set_col((cl_float4){0.0f, 1.0f, 0.0f, 0.0f});
    l.set_shadow_casting(0);
    l.set_brightness(1);
    l.set_pos((cl_float4){-200, 100, 0});
    //l.set_pos((cl_float4){-150, 150, 300});
    l.radius = 1000000;
    /*l.set_pos((cl_float4){-200, 2000, -100, 0});
    l.set_pos((cl_float4){-200, 200, -100, 0});
    l.set_pos((cl_float4){-400, 150, -555, 0});*/
    window.add_light(&l);

    l.set_col((cl_float4){1.0f, 0.0f, 1.0f, 0});

    l.set_pos((cl_float4){-0, 200, -500, 0});
    l.shadow = 0;
    l.radius = 1000000;

    window.add_light(&l);

    //window.set_camera_pos({0, 100, 200});
    //window.set_camera_rot({0.1, M_PI, 0});

    /*l.set_col({1.0, 0.5, 0.0});
    l.set_pos((cl_float4){-0, 2000,-0, 0});
    l.set_shadow_casting(1);

    window.add_light(&l);

    l.set_col({0, 0.5, 0.99});
    l.set_pos((cl_float4){-1200, 250,0, 0});
    l.set_shadow_casting(1);

    window.add_light(&l);*/


    window.construct_shadowmaps();

    int times[10] = {0};
    int time_count = 0;

    int load_first = 0;

    while(window.window.isOpen())
    {
        ///rift
        //ovrHmd_BeginFrame(HMD, 0);
        ///endrift


        sf::Clock c;

        if(window.window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                window.window.close();
        }

        for(int i=0; i<zebra_count; i++)
        {
            zebra::update(&zebras[i]);
        }

        window.c_pos.y += 10.0f;

        window.input();

        window.draw_bulk_objs_n();

        window.render_buffers();

        times[time_count] = c.getElapsedTime().asMicroseconds();

        time_count = (time_count + 1) % 10;

        int time = 0;

        for(int i=0; i<10; i++)
        {
            time += times[i];
        }

        if(!load_first)
        {
            std::cout << "time to load and execute 1 frame = " << load_time.getElapsedTime().asSeconds();
            load_first = 1;
        }

        //std::cout << time/10 << std::endl;

        std::cout << c.getElapsedTime().asMicroseconds() << std::endl;

        ///rift

        ///endrift



        ///raw time
        //std::cout << c.getElapsedTime().asMicroseconds() << std::endl;
    }
}