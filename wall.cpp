#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "wall.hpp"
void wall::update(float *time_elapsed, std::vector<entity *> *all_objects)
{//przeciążenie update dla ściany, nic się nie dzieje
}
wall::wall()
{
    setFillColor(sf::Color(80, 80, 80));
    setSize(sf::Vector2f(5000.0, 5000.0));
    setPosition(-5000, -2500);
}
