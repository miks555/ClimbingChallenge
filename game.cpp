#define SFML_STATIC
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "hero.hpp"
#include "wall.hpp"
#include "platform.hpp"
#include "crate.hpp"
#include "rock.hpp"
#include "supplies_bar.hpp"
#include "drawable_text.hpp"
void game::update()
{
    while (window_0->pollEvent(*event_0)) // eventy
    {
        if (event_0->type == sf::Event::Closed)
        {
            window_0->close();
            *run = 0;
        }
        if (event_0->type == sf::Event::Resized)
        {
            view_0->setSize(event_0->size.width, event_0->size.height);
        }
        if (event_0->type == sf::Event::TextEntered)
        {
            if (event_0->text.unicode == 32)
            {
                dynamic_cast<hero *>(all_objects->at(0))->set_jump();
            }
        }
    }
    *time_elapsed = clock_0->restart().asSeconds();
    for (int i = 0; i < all_objects->size(); i++) // aktualizacja położeń animacji kolizji itp
    {
        all_objects->at(i)->update(time_elapsed, all_objects);
    }
    int iter_1 = 0; // wyznaczenie miejsca dolnej platformy i ewentualny despawn
    while (dynamic_cast<platform *>(all_objects->at(iter_1)) == nullptr)
    {
        iter_1++;
    }
    if (fabsf((dynamic_cast<platform *>(all_objects->at(iter_1))->getPosition().y) - (dynamic_cast<hero *>(all_objects->at(0))->getPosition().y)) > 800)
    {
        delete all_objects->at(iter_1);
        all_objects->erase(all_objects->begin() + iter_1);
    }
    int iter_2 = all_objects->size() - 1; // wyznaczenie miejsca górnej platformy i ewentualny spawn
    while (dynamic_cast<platform *>(all_objects->at(iter_2)) == nullptr)
    {
        iter_2--;
    }
    if (fabsf((dynamic_cast<platform *>(all_objects->at(iter_2))->getPosition().y) - (dynamic_cast<hero *>(all_objects->at(0))->getPosition().y)) < 5000)
    { // spawnowanie odbywa się trohę losowo z uwzględnieniem pozycji górnej platformy i bohatera
        all_objects->emplace_back(new platform(((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width)) + (double)rand() / RAND_MAX * (((dynamic_cast<wall *>(all_objects->at(4))->getGlobalBounds().left) - (dynamic_cast<platform *>(all_objects->at(iter_2))->getGlobalBounds().width)) - ((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width))), dynamic_cast<platform *>(all_objects->at(iter_2))->getGlobalBounds().top - (20 + (double)rand() / RAND_MAX * (220))));
        (dynamic_cast<platform *>(all_objects->at(all_objects->size() - 1)))->setTexture(texture_platform);
    }
    for (int i = 0; i < all_objects->size(); i++) // despawn skrzynek
    {
        if (dynamic_cast<crate *>(all_objects->at(i)) != nullptr)
        {

            if (fabsf((dynamic_cast<crate *>(all_objects->at(i))->getPosition().y) - (dynamic_cast<hero *>(all_objects->at(0))->getPosition().y)) > 5000)
            {
                delete all_objects->at(i);
                all_objects->erase(all_objects->begin() + i);
            }
        }
    }
    int count_0 = 0; // zliczenie skrzynek i ewentualny spawn
    for (int i = 0; i < all_objects->size(); i++)
    {
        if (dynamic_cast<crate *>(all_objects->at(i)) != nullptr)
        {
            count_0++;
        }
    }
    if (count_0 < 20 && (double)rand() / RAND_MAX <= *crate_chance && clock_1->getElapsedTime().asSeconds() > 5)
    { // uwzględnia się w spawnie czas i ilość, pozycję ścian i bohatera
        clock_1->restart();
        all_objects->emplace_back(new crate(((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width)) + (double)rand() / RAND_MAX * (((dynamic_cast<wall *>(all_objects->at(4))->getGlobalBounds().left) - 35.4) - ((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width))), dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - 1000));
        (dynamic_cast<crate *>(all_objects->at(all_objects->size() - 1)))->setTexture(texture_crate);
    }
    for (int i = 0; i < all_objects->size(); i++) // despawn skał
    {
        if (dynamic_cast<rock *>(all_objects->at(i)) != nullptr)
        {
            if (fabsf((dynamic_cast<rock *>(all_objects->at(i))->getPosition().y) - (dynamic_cast<hero *>(all_objects->at(0))->getPosition().y)) > 5000)
            {
                delete all_objects->at(i);
                all_objects->erase(all_objects->begin() + i);
            }
        }
    }
    int count_1 = 0; // zliczenie skał i ewentualny despawn
    for (int i = 0; i < all_objects->size(); i++)
    {
        if (dynamic_cast<rock *>(all_objects->at(i)) != nullptr)
        {
            count_1++;
        }
    }
    if (count_1 < 1000 && (double)rand() / RAND_MAX <= *rock_chance && clock_2->getElapsedTime().asSeconds() > *rock_time)
    { // uwzględnia się w spawnie czas i ilość, pozycję ścian i bohatera
        clock_2->restart();
        all_objects->emplace_back(new rock(((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width)) + (double)rand() / RAND_MAX * (((dynamic_cast<wall *>(all_objects->at(4))->getGlobalBounds().left) - 96.4) - ((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width))), dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - 1000));
        (dynamic_cast<rock *>(all_objects->at(all_objects->size() - 1)))->setTexture(texture_rock);
    }
    if (clock_3->getElapsedTime().asSeconds() > 10)
    { // skały pojawiają się coraz częściej
        clock_3->restart();
        *rock_time = *rock_time - 0.05;
        if (*rock_time < 1)
        {
            *rock_time = 1;
        }
    } // aktualizajcia pozycji paska zaopatrzenia, wyniku, ścian, kamery
    dynamic_cast<supplies_bar *>(all_objects->at(1))->setPosition(dynamic_cast<supplies_bar *>(all_objects->at(1))->getPosition().x, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - 300);
    dynamic_cast<supplies_bar *>(all_objects->at(1))->setSize(sf::Vector2f(*(dynamic_cast<hero *>(all_objects->at(0))->get_supplies_level()), dynamic_cast<supplies_bar *>(all_objects->at(1))->getSize().y));
    dynamic_cast<drawable_text *>(all_objects->at(2))->setPosition((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width) - dynamic_cast<drawable_text *>(all_objects->at(2))->getGlobalBounds().width - 5, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - 350);
    dynamic_cast<drawable_text *>(all_objects->at(2))->setString("altitude " + std::to_string(-(*(dynamic_cast<hero *>(all_objects->at(0))->get_points()))));
    dynamic_cast<wall *>(all_objects->at(3))->setPosition(sf::Vector2f(dynamic_cast<wall *>(all_objects->at(3))->getPosition().x, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - dynamic_cast<wall *>(all_objects->at(3))->getSize().y / 2));
    dynamic_cast<wall *>(all_objects->at(4))->setPosition(sf::Vector2f(dynamic_cast<wall *>(all_objects->at(4))->getPosition().x, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top - dynamic_cast<wall *>(all_objects->at(3))->getSize().y / 2));
    view_0->setCenter(sf::Vector2f(view_0->getCenter().x, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top + dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().height / 2));
}
game::~game()
{
    delete time_elapsed; // zwolnienie pamięci
    delete view_0;
    delete icon_0;
    delete texture_crate;
    delete texture_platform;
    delete texture_rock;
    delete run;
    delete window_0;
    delete event_0;
    delete clock_0;
    delete clock_1;
    delete clock_2;
    delete clock_3;
    delete music_0;
    delete rock_chance;
    delete rock_time;
    delete crate_chance;
    delete supply_drop_rate;
    for (int i = 0; i < all_objects->size(); i++)
    {
        delete all_objects->at(i);
    }
    delete all_objects;
}
game::game(bool fullscreen, float rock_chance_arg, float crate_chance_arg, float supply_drop_rate_arg)
{
    srand(time(NULL));                               // ziarno generatora
    texture_crate = new sf::Texture;                 // tworzenie wstępnych obiektów
    texture_crate->loadFromFile("assets/crate.png"); // tekstury
    texture_platform = new sf::Texture;
    texture_platform->loadFromFile("assets/platform.png");
    texture_rock = new sf::Texture;
    texture_rock->loadFromFile("assets/rock.png");
    all_objects = new std::vector<entity *>;
    time_elapsed = new float;
    *time_elapsed = 0;
    rock_time = new float;
    *rock_time = 5;
    view_0 = new sf::View;
    icon_0 = new sf::Image;
    run = new bool;
    window_0 = new sf::RenderWindow;
    event_0 = new sf::Event;
    clock_0 = new sf::Clock;
    clock_1 = new sf::Clock;
    clock_2 = new sf::Clock;
    clock_3 = new sf::Clock;
    music_0 = new sf::Music;
    rock_chance = new float;
    crate_chance = new float;
    supply_drop_rate = new float;
    all_objects->emplace_back(new hero); // bohater
    dynamic_cast<hero *>(all_objects->at(0))->set_supply_drop_rate(supply_drop_rate);
    all_objects->emplace_back(new supplies_bar);  // pasek zaopatrzenia
    all_objects->emplace_back(new drawable_text); // punkty
    all_objects->emplace_back(new wall);          // ściany
    all_objects->emplace_back(new wall);
    dynamic_cast<wall *>(all_objects->at(4))->move(dynamic_cast<wall *>(all_objects->at(4))->getSize().x + 600, 0);                                                                                                                                                                                                                                                                                                                                                                    // przesunięcie prawej śćiany
    all_objects->emplace_back(new platform(0, (dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().height) + 5));                                                                                                                                                                                                                                                                                                                                                              // utworzenie startowej platformy
    dynamic_cast<platform *>(all_objects->at(5))->setTexture(texture_platform);                                                                                                                                                                                                                                                                                                                                                                                                        // i jej tekstury
    dynamic_cast<supplies_bar *>(all_objects->at(1))->setPosition((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width) - dynamic_cast<supplies_bar *>(all_objects->at(1))->getGlobalBounds().width, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top + dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().height / 2);                                                     // pozycja
    dynamic_cast<drawable_text *>(all_objects->at(2))->setPosition((dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width) - dynamic_cast<drawable_text *>(all_objects->at(2))->getGlobalBounds().width, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top + dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().height / 2);                                                   // pozycja
    *(view_0) = sf::View(sf::FloatRect(((dynamic_cast<wall *>(all_objects->at(4))->getGlobalBounds().left) - (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().left) + (dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds().width)) / 2, dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().top + dynamic_cast<hero *>(all_objects->at(0))->getGlobalBounds().height / 2, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)); // pozycja
    view_0->setCenter(300, 2);                                                                                                                                                                                                                                                                                                                                                                                                                                                         // wyśrodkowanie kamery
    icon_0->loadFromFile("assets/icon.png");
    *run = 1;       // okno włąćzone
    if (fullscreen) // utworzenie okna z parametru z menu
    {
        window_0->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "game", sf::Style::Fullscreen);
    }
    else
    {
        window_0->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "game", sf::Style::Default);
    }
    window_0->setIcon(icon_0->getSize().x, icon_0->getSize().y, icon_0->getPixelsPtr());
    window_0->setVerticalSyncEnabled(true); // synchronizacja wertykalna
    window_0->setView(*view_0);
    window_0->setKeyRepeatEnabled(false);      // dzięki temu wziśnięcie spacji generuje 1 event
    music_0->openFromFile("assets/music.wav"); // tło dźwiękowe
    music_0->setLoop(true);
    music_0->play();
    *rock_chance = rock_chance_arg;
    *crate_chance = crate_chance_arg;
    *supply_drop_rate = supply_drop_rate_arg;
}
bool *game::running()
{
    return run;
}
void game::render()
{ // wszystko się rysuje
    window_0->clear(sf::Color(66, 179, 245));
    window_0->setView(*view_0);
    for (int i = all_objects->size() - 1; i >= 0; i--)
    {
        if (dynamic_cast<hero *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<hero *>(all_objects->at(i))));
        }
        if (dynamic_cast<wall *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<wall *>(all_objects->at(i))));
        }
        if (dynamic_cast<crate *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<crate *>(all_objects->at(i))));
        }
        if (dynamic_cast<drawable_text *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<drawable_text *>(all_objects->at(i))));
        }
        if (dynamic_cast<platform *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<platform *>(all_objects->at(i))));
        }
        if (dynamic_cast<rock *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<rock *>(all_objects->at(i))));
        }
        if (dynamic_cast<supplies_bar *>(all_objects->at(i)) != nullptr)
        {
            window_0->draw(*(dynamic_cast<supplies_bar *>(all_objects->at(i))));
        }
    }
    window_0->display();
}