#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/game.h"
#include "src/window.h"
#include <iostream>
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    sf::Clock clock;

    while(!window.IsDone()){
    window.StartWindow();
    Game game(window);
    while(!game.IsWindowDone() && !game.IsDone()){
        sf::Time elapsedTime = clock.restart();
        float time_warp = elapsedTime.asSeconds();
        game.GameUpdate(time_warp);
    }
    }
    //game.EndGame();
    return 0;
}