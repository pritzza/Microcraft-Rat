#include "Game.h"

int main()
{
    Game game{ 256, 144, 12, "Game", sf::Style::Default };

    game.start();

    return 0;
}