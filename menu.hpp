#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class menu
{
private:
    sf::Image *icon_0;
    bool *fullscreen;
    float *rock_chance;
    float *crate_chance;
    float *supply_drop_rate;
    sf::RenderWindow *window_0;
    sf::Font *font_0;
    sf::Text *text_fullscreen;
    sf::Text *text_difficulty;
    sf::Text *text_ok;
    sf::Event *event_0;
    bool *run;
    int *level;
    sf::Music *music_0;//muzyka w menu

public:
    menu();
    ~menu();
    void update();
    void render();
    bool *running();
    bool get_fullscreen();
    float get_rock_chance();
    float get_crate_chance();
    float get_supply_drop_rate();
};