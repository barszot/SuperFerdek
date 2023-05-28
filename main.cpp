#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/game.h"
#include "src/window.h"
#include <fstream>
#include <iostream>
#include "libs/json.hpp"
#include <string>
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    sf::Clock clock;

    int max_level = 3;

    while(!window.get_is_done()){
    bool is_loading_saved_game = window.start_window();
    std::ifstream f("data.json");
    nlohmann::json data;
    f>>data;
    int level = data["level"];
    int lives = data["lives"];
    int coins_earned_earlier = data["coins_earned_earlier"];
    bool is_big = data["is_big"];
    int highscore = data["highscore"];

    Game game(window, max_level);
    if(is_loading_saved_game)
    {
        game.load_game(level, lives, coins_earned_earlier, is_big);
    }

    while(!game.get_is_window_done() && !game.get_is_done()){
        sf::Time elapsedTime = clock.restart();
        float delta_time = elapsedTime.asSeconds();
        game.game_update(delta_time);
    }
    if(!window.get_is_done()){
    if(game.get_is_won())
    {
        int result = game.get_coins_earned_earlier();

        window.end_window_after_win(result, highscore);
    }
    else
    {
        window.end_window_after_lost();
    }
    }
    }
    return 0;
}