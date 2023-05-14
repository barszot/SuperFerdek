#include <SFML/Graphics.hpp>
#include "src/game.h"

#include <iostream>
int main()
{
    Game game;

    while(!game.IsDone()){
        game.GameUpdate();
    }
    game.EndGame();
    return 0;
}