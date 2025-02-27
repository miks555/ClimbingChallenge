#include "menu.hpp"
#include "game.hpp"
int main()
{//assety z https://pixabay.com/
    menu *menu_0 = new menu;//tworzę menu
    while (*(menu_0->running()))
    {
        menu_0->update();
        menu_0->render();
    }//tworzę gre na podstawie danych z menu
    game *game_0 = new game(menu_0->get_fullscreen(), menu_0->get_rock_chance(), menu_0->get_crate_chance(), menu_0->get_supply_drop_rate());
    delete menu_0;
    while (*(game_0->running()))
    {
        game_0->update();
        game_0->render();
    }
    delete game_0;
    return 0;
}