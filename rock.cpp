#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "rock.hpp"
#include <math.h>
void rock::update(float *time_elapsed, std::vector<entity *> *all_objects)
{ // przeciążenie update dla skały, animacja i ruch
    *animation_time = *animation_time + *time_elapsed;
    float period = 0.5;
    if (*animation_time >= period / 5)
    {
        *animation_time = *animation_time - period * floorf(*animation_time / (period));
        while (*animation_time >= period / 5)
        {
            *animation_state = *animation_state + 1;
            *animation_time = *animation_time - period / 5;
            if (*animation_state > 4)
            {
                *animation_state = 0;
            }
        }
    }
    setTextureRect(sf::IntRect(964 * (*animation_state), 0, 964, 964));
    move(sf::Vector2f(0, *time_elapsed * (50)));
}
rock::rock(float x, float y)
{
    animation_time = new float;
    *animation_time = 0;
    animation_state = new int;
    *animation_state = 0;
    setTextureRect(sf::IntRect(0, 0, 964, 964));
    setSize(sf::Vector2f(964, 964));
    setScale(0.1, 0.1);
    setPosition(x, y);
}
rock::~rock()
{
    delete animation_time; // zwolnienie pamięci
    delete animation_state;
}