#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "platform.hpp"
void platform::update(float *time_elapsed, std::vector<entity *> *all_objects)
{//przeciążenie update dla platformy, nic się nie dzieje
}
platform::platform(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
    setTextureRect(sf::IntRect(0, 0, 1236, 232));
    setSize(sf::Vector2f(1236, 232));
    setScale(0.1, 0.1);
}