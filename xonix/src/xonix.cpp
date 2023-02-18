#include "Gameplay.hpp"
#include "Render.hpp"

#include "Game.hpp"

int main()
{
    xon::Game game;

    game.init();

    game.loop();

    game.close();

    return 0;
}
