#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "crate.hpp"
#include <math.h>
void crate::update(float *time_elapsed, std::vector<entity *> *all_objects) // przeciążenie update dla skrzynki, tylko animacja
{
    *animation_time = *animation_time + *time_elapsed;
    float period = 2;
    if (*animation_time >= period / 2)
    {
        *animation_time = *animation_time - period * floorf(*animation_time / (period));
        if (*animation_time >= period / 2)
        {
            *animation_state = !(*animation_state);
            *animation_time = *animation_time - period / 2;
        }
    }
    setTextureRect(sf::IntRect(708 * (*animation_state), 0, 708, 708));
}
crate::crate(float x, float y) // konstruktor umożliwiający spawnowanie na punkcie (x,y)
{
    animation_time = new float;
    *animation_time = 0;
    animation_state = new bool;
    *animation_state = 0;
    setTextureRect(sf::IntRect(0, 0, 708, 708));
    setSize(sf::Vector2f(708, 708));
    setScale(0.05, 0.05);
    setPosition(x, y);
}
crate::~crate()
{
    delete animation_time; // zwolnienie pamięci
    delete animation_state;
}