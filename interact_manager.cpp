#include "interact_manager.hpp"
#include <SFML/Graphics.hpp>
#include "engine.hpp"

bool interact::is_loaded = false;
sf::Image interact::pixel;
sf::Texture interact::texture_pixel;
sf::RenderWindow* interact::render_window;
std::vector<std::pair<int,int> > interact::pixel_stack;
std::vector<std::pair<point,point> > interact::rectangle_stack;

void interact::set_render_window(sf::RenderWindow* win)
{
    render_window = win;
    if(!is_loaded)
    {
        load();
    }
}

void interact::load()
{
    if(is_loaded)
        return;

    pixel.create(1,1, sf::Color(255,0,0));
    texture_pixel.loadFromImage(pixel);

    is_loaded = true;
}

void interact::draw_pixel(int x, int y)
{
    pixel_stack.push_back(std::make_pair(x, engine::height - y));
}

void interact::draw_rect(int x1, int y1, int x2, int y2)
{
    point one = {x1, engine::height - y1};
    point two = {x2, engine::height - y2};

    rectangle_stack.push_back(std::make_pair<point, point>(one, two));
}

void interact::deplete_stack()
{
    sf::Sprite spr;

    spr.setTexture(texture_pixel);

    for(int i=0; i<pixel_stack.size(); i++)
    {
        int x = pixel_stack[i].first;
        int y = pixel_stack[i].second;

        spr.setPosition(x, y);

        render_window->draw(spr);
    }

    for(int i=0; i<rectangle_stack.size(); i++)
    {
        point one, two;
        one = rectangle_stack[i].first;
        two = rectangle_stack[i].second;

        ///must be specified tl tr

        sf::RectangleShape rshape;

        rshape.setPosition(one.x, one.y);
        rshape.setSize(sf::Vector2f(1, 5));
        render_window->draw(rshape);

        rshape.setPosition(two.x, one.y);
        render_window->draw(rshape);

        rshape.setPosition(one.x, two.y - 4);
        render_window->draw(rshape);

        rshape.setPosition(two.x, two.y - 4);
        render_window->draw(rshape);

        rshape.setSize(sf::Vector2f(5, 1));
        rshape.setPosition(one.x, one.y);
        render_window->draw(rshape);

        rshape.setPosition(two.x - 4, one.y);
        render_window->draw(rshape);

        rshape.setPosition(one.x, two.y);
        render_window->draw(rshape);

        rshape.setPosition(two.x - 4, two.y);
        render_window->draw(rshape);
    }


    pixel_stack.clear();
    rectangle_stack.clear();
}