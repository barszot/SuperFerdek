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
        float delta_time = elapsedTime.asSeconds();
        game.GameUpdate(delta_time);
    }
    if(!window.get_is_done()){
    if(game.get_is_won())
    {
        unsigned int result = game.get_coins_earned_earlier();

        std::cout<<"WYgRALES!! "<<result<<"\n";
    }
    else
    {
        std::cout<<"przegrales!!\n";
        window.end_window_after_lost();


    }
    }
    }
    //game.EndGame();
    return 0;
}