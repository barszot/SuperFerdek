#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/game.h"

#include <iostream>
int main()
{
    
    sf::Clock clock;

    Game game;
    while(!game.IsDone()){
        sf::Time elapsedTime = clock.restart();
        float time_warp = elapsedTime.asSeconds();
        game.GameUpdate(time_warp);
    }
    game.EndGame();
    return 0;
}