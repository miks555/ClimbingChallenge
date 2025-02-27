#include <vector>
#include "entity.hpp"
class game
{
private:
    std::vector<entity *> *all_objects;//wektor obiektów a dokładniej to wskaźników na obiekty
    float *time_elapsed;
    sf::View *view_0; //widok
    sf::Image *icon_0; //ikona okna
    bool *run; //czy okno włączone
    sf::RenderWindow *window_0;
    sf::Event *event_0;
    sf::Clock *clock_0; //zegar głównej pętli
    sf::Clock *clock_1; //zegar spawniwania skrzynki
    sf::Clock *clock_2; //zegar spawniwania skał
    sf::Clock *clock_3; //zegar zmienia częstość spawniwania skał
    sf::Music *music_0; //muzyka w tle
    sf::Texture *texture_crate;
    sf::Texture *texture_platform;
    sf::Texture *texture_rock;
    float *rock_chance; //szansa na skałe
    float *rock_time; //wpływa na częstość spawniwania skał
    float *crate_chance; //szansa na skrzynke
    float *supply_drop_rate; //szybkość spadku paska zaopatrzenia

public:
    game(bool fullscreen, float rock_chance_arg, float crate_chance_arg, float supply_drop_rate_arg);
    ~game(); 
    void update(); //aktualizacja obiektów
    void render(); //rysowanie obiektów
    bool *running();
};