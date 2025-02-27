#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.hpp"
#include "drawable_text.hpp"
void drawable_text::update(float *time_elapsed, std::vector<entity *> *all_objects) //przeciążenie update dla tekstu, nic się nie dzieje
{
}
drawable_text::drawable_text()//tekst ładuje times.ttf bo i tak jest tylko jeden w grze
{
    font_0 = new sf::Font;
    font_0->loadFromFile("assets/times.ttf");
    setFont(*font_0);
    setString("Hello world");
    setCharacterSize(24);
    setFillColor(sf::Color::Black);
    setStyle(sf::Text::Bold);
    setPosition(sf::Vector2f(0, 0));
}

drawable_text::~drawable_text()
{
    delete font_0;
}