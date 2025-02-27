#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "supplies_bar.hpp"
void supplies_bar::update(float *time_elapsed, std::vector<entity *> *all_objects)
{//przeciążenie update dla pasaka, nic się nie dzieje
}
supplies_bar::supplies_bar()
{
    setPosition(sf::Vector2f(0, 0));
    setFillColor(sf::Color::Green);
    setSize(sf::Vector2f(200, 50));
}