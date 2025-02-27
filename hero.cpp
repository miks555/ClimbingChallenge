#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <math.h>
#include "entity.hpp"
#include "hero.hpp"
#include "wall.hpp"
#include "platform.hpp"
#include "crate.hpp"
#include "rock.hpp"
#include "drawable_text.hpp"
void hero::update(float *time_elapsed, std::vector<entity *> *all_objects)
{
    update_animation();
    update_positions(time_elapsed);
    update_supplies(time_elapsed);
    update_velocity(time_elapsed);
    decollide(all_objects);
    collide(all_objects);
}
float *hero::get_points()
{
    return points;
}
float *hero::get_supplies_level()
{
    return supplies_level;
}
void hero::collide(std::vector<entity *> *all_objects)
{//zderzenia z skałą i skrzynką
    for (int i = 0; i < all_objects->size(); i++)
    {
        if (dynamic_cast<crate *>(all_objects->at(i)) != nullptr)
        {
            if (dynamic_cast<crate *>(all_objects->at(i))->getGlobalBounds().intersects(getGlobalBounds()))
            {
                delete all_objects->at(i);
                all_objects->erase(all_objects->begin() + i);
                *supplies_level = *supplies_level + 20;
                if (*supplies_level > 200)
                {
                    *supplies_level = 200;
                }
                i = -1;
                sound_1->play();
            }
        }
        else
        {
            if (dynamic_cast<rock *>(all_objects->at(i)) != nullptr)
            {
                if (dynamic_cast<rock *>(all_objects->at(i))->getGlobalBounds().intersects(getGlobalBounds()))
                {
                    delete all_objects->at(i);
                    all_objects->erase(all_objects->begin() + i);
                    *supplies_level = *supplies_level - 20;
                    if (*supplies_level < 0)
                    {
                        *supplies_level = 0;
                    }
                    i = -1;
                    sound_2->play();
                }
            }
        }
    }
}
void hero::set_jump()
{//skok
    if (*is_jumping == 0)
    {
        *is_jumping = 1;
        *velocity_y = -450;
        sound_0->play();
    }
}
hero::~hero()
{
    delete supplies_level;//zwolnienie pamięci
    delete points;
    delete velocity_x;
    delete velocity_y;
    delete animation_state;
    delete acceleration_y;
    delete previous_x;
    delete previous_y;
    delete is_jumping;
    delete buffer_0;
    delete sound_0;
    delete buffer_1;
    delete sound_1;
    delete buffer_2;
    delete sound_2;
    delete texture_0;
}
hero::hero()
{
    buffer_0 = new sf::SoundBuffer;//wstępne załadowanie
    buffer_0->loadFromFile("assets/jump.wav");
    sound_0 = new sf::Sound;
    sound_0->setBuffer(*buffer_0);
    texture_0 = new sf::Texture;
    texture_0->loadFromFile("assets/hero.png");
    texture_0->setRepeated(true);
    buffer_1 = new sf::SoundBuffer;
    buffer_1->loadFromFile("assets/crate.wav");
    sound_1 = new sf::Sound;
    sound_1->setBuffer(*buffer_1);
    buffer_2 = new sf::SoundBuffer;
    buffer_2->loadFromFile("assets/rock.wav");
    sound_2 = new sf::Sound;
    sound_2->setBuffer(*buffer_2);
    setTextureRect(sf::IntRect(0, 0, 8, 12));
    setTexture(texture_0);
    setSize(sf::Vector2f(8, 12));
    setScale(3, 3);
    setPosition(0, 0);
    supplies_level = new float;
    *supplies_level = 200;
    points = new float;
    velocity_x = new float;
    *velocity_x = 0;
    velocity_y = new float;
    *velocity_y = 0;
    animation_state = new int;
    *animation_state = 0;
    acceleration_y = new float;
    *acceleration_y = 400;
    previous_x = new float;
    *previous_x = getPosition().x;
    previous_y = new float;
    *previous_y = getPosition().y;
    is_jumping = new bool;
    *is_jumping = 0;
    supply_drop_rate = new float;
}
void hero::set_supply_drop_rate(float *supply_drop_rate_arg)
{
    supply_drop_rate = supply_drop_rate_arg;
}
void hero::update_positions(float *time_elapsed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        *velocity_x = -500;
        *animation_state = 0;
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            *velocity_x = 500;
            *animation_state = 1;
        }
        else
        {
            *velocity_x = 0;
        }
    }
    *previous_x = getPosition().x;
    *previous_y = getPosition().y;
    move(sf::Vector2f(*time_elapsed * *velocity_x, *time_elapsed * *velocity_y + 0.5 * *acceleration_y * *time_elapsed * *time_elapsed));//przesunięcie
}
void hero::update_velocity(float *time_elapsed)
{
    *velocity_y = *velocity_y + *acceleration_y * *time_elapsed;//prędkość zmiana
    if (fabsf(*velocity_y) > 1000)//upadek koniec gry
    {
        sf::sleep(sf::milliseconds(7000));
        exit(0);
    }
}
void hero::decollide(std::vector<entity *> *all_objects)
{//kolizja z platformą lub ścianą, chciałem dać jakiś algorytm kolizji ale to słabo działało bo float gubił dokładność na wysokośći > 2048 (hyba)
    while (getGlobalBounds().intersects(dynamic_cast<wall *>(all_objects->at(3))->getGlobalBounds()))
    {//lewa ściana
        move(0.01, 0);
    }
    while (getGlobalBounds().intersects(dynamic_cast<wall *>(all_objects->at(4))->getGlobalBounds()))
    {//prawa ściana
        move(-0.01, 0);
    }
    if (*velocity_y >= 0)
    {//platforma, wejśćie na platformę gdy nogi bohatera wyżej niż duł platformy
        for (int i = 0; i < all_objects->size(); i++)
        {
            if (dynamic_cast<platform *>(all_objects->at(i)) != nullptr)
            {
                if (getGlobalBounds().top + getGlobalBounds().height < (dynamic_cast<platform *>(all_objects->at(i))->getGlobalBounds().top + dynamic_cast<platform *>(all_objects->at(i))->getGlobalBounds().height))
                {
                    while (getGlobalBounds().intersects(dynamic_cast<platform *>(all_objects->at(i))->getGlobalBounds()))
                    {
                        move(0, -0.01);
                        *velocity_y = 0;
                        *is_jumping = 0;
                    }
                }
            }
        }
    }
}
void hero::update_supplies(float *time_elapsed)
{//spadek paska
    if (*points > getPosition().y)
    {
        *points = getPosition().y;
    }
    *supplies_level = *supplies_level - *time_elapsed * *supply_drop_rate;
    if (*supplies_level < 0)
    {//przegrana
        sf::sleep(sf::milliseconds(7000));
        exit(0);
    }
}
void hero::update_animation()
{//nie komentuje niektórych rzeczy bo wydają mi się oczywiste
    if (fabsf(*velocity_y) <= 2 and *animation_state == 0)
    {
        setTextureRect(sf::IntRect(8, 0, 8, 12));
    }
    if (fabsf(*velocity_y) <= 2 and *animation_state == 1)
    {
        setTextureRect(sf::IntRect(0, 0, 8, 12));
    }
    if (fabsf(*velocity_y) > 2 and *animation_state == 0)
    {
        setTextureRect(sf::IntRect(24, 0, 8, 12));
    }
    if (fabsf(*velocity_y) > 2 and *animation_state == 1)
    {
        setTextureRect(sf::IntRect(16, 0, 8, 12));
    }
}