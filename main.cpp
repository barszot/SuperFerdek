#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/game.h"
#include "src/window.h"
#include <iostream>
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    sf::Clock clock;

    while(!window.get_is_done()){
    window.start_window();
    Game game(window, 3);
    while(!game.IsWindowDone() && !game.IsDone()){
        sf::Time elapsedTime = clock.restart();
        float time_warp = elapsedTime.asSeconds();
        game.GameUpdate(time_warp);
    }
    if(game.get_is_won())
    {
        std::cout<<"WYgRALES!!\n";
    }
    else
    {
        std::cout<<"przegrales!!\n";

    }
    }
    //game.EndGame();
    return 0;
}