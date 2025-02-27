#include "menu.hpp"
void menu::update()
{
    while (window_0->pollEvent(*event_0))
    {//eventy
        if (event_0->type == sf::Event::Closed)
        {
            exit(0);
        }
        if (event_0->type == sf::Event::MouseButtonPressed)
        {
            if (event_0->mouseButton.button == sf::Mouse::Left)
            {//obsługa menu
                if (text_ok->getGlobalBounds().contains(event_0->mouseButton.x, event_0->mouseButton.y))
                {
                    *run = 0;
                }
                if (text_fullscreen->getGlobalBounds().contains(event_0->mouseButton.x, event_0->mouseButton.y))
                {
                    *fullscreen = !(*fullscreen);
                }
                if (text_difficulty->getGlobalBounds().contains(event_0->mouseButton.x, event_0->mouseButton.y))
                {
                    (*level)++;
                }
            }
        }
    }
    if (*level > 1)
    {
        *level = 0;
    }
    if (*fullscreen)
    {
        text_fullscreen->setString("fullscreen on");
    }
    else
    {
        text_fullscreen->setString("fullscreen off");
    }
    if (*level == 0)
    {//ustalenie parametrów trudnośći
        *rock_chance = 0.5;
        *crate_chance = 0.8;
        *supply_drop_rate = 2;
        text_difficulty->setString("difficulty normal");
    }
    if (*level == 1)
    {
        *rock_chance = 0.8;
        *crate_chance = 0.5;
        *supply_drop_rate = 5;
        text_difficulty->setString("difficulty hard");
    }
}
menu::~menu()
{
    delete icon_0; //zwolnienie pamięci
    delete fullscreen;
    delete rock_chance;
    delete crate_chance;
    delete supply_drop_rate;
    delete window_0;
    delete font_0;
    delete text_fullscreen;
    delete text_difficulty;
    delete text_ok;
    delete event_0;
    delete run;
    delete level;
    delete music_0;
}
menu::menu()
{
    icon_0 = new sf::Image;//wstępna inicjalizacja
    fullscreen = new bool;
    rock_chance = new float;
    crate_chance = new float;
    supply_drop_rate = new float;
    window_0 = new sf::RenderWindow;
    font_0 = new sf::Font;
    text_fullscreen = new sf::Text;
    text_difficulty = new sf::Text;
    text_ok = new sf::Text;
    event_0 = new sf::Event;
    run = new bool;
    level = new int;
    music_0 = new sf::Music;
    icon_0->loadFromFile("assets/icon.png");
    *fullscreen = 0;
    window_0->create(sf::VideoMode(200, 100), "menu", sf::Style::Titlebar | sf::Style::Close);
    window_0->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window_0->getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window_0->getSize().y / 2));
    window_0->setIcon(icon_0->getSize().x, icon_0->getSize().y, icon_0->getPixelsPtr());
    window_0->setVerticalSyncEnabled(true);
    font_0->loadFromFile("assets/times.ttf");
    text_fullscreen->setFont(*font_0);
    text_fullscreen->setCharacterSize(24);
    text_fullscreen->setFillColor(sf::Color::Black);
    text_fullscreen->setStyle(sf::Text::Bold);
    text_fullscreen->setPosition(sf::Vector2f(0, 0));
    *text_difficulty = *text_fullscreen;
    text_difficulty->move(0, 24);
    *text_ok = *text_fullscreen;//skopiowanie z przesunięciem
    text_ok->move(0, 48);
    text_ok->setString("ok");
    *run = 1;
    *level = 0;
    music_0->openFromFile("assets/music.wav");
    music_0->setLoop(true);
    music_0->play();
}
bool *menu::running()
{
    return run;
}
bool menu::get_fullscreen()
{
    return *fullscreen;
}
float menu::get_rock_chance()
{
    return *rock_chance;
}
float menu::get_crate_chance()
{
    return *crate_chance;
}
float menu::get_supply_drop_rate()
{
    return *supply_drop_rate;
}
void menu::render()
{
    window_0->clear(sf::Color::White);
    window_0->draw(*text_ok);
    window_0->draw(*text_difficulty);
    window_0->draw(*text_fullscreen);
    window_0->display();
}