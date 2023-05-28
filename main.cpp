#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "src/game.h"
#include "src/window.h"
#include <iostream>
#include <fstream>
#include "libs/json.hpp"
#include <string>
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    sf::Clock clock;
    /*sf::Music music;
    
    // Wczytaj plik muzyczny
    if (!music.openFromFile("src/sounds/sf_theme_song.ogg"))
        return -1; // Błąd wczytywania pliku

    // Odtwórz muzykę
    music.play();
    */

    int max_level = 3;

    std::ifstream f("data.json");
    nlohmann::json data;
    f>>data;
    int level = data["level"];
    int lives = data["lives"];
    int coins_earned_earlier = data["coins_earned_earlier"];
    bool is_big = data["is_big"];
    int highscore = data["highscore"];
    std::cout<<"json test: "<<level<<" "<<lives<<" "<<coins_earned_earlier<<" "<<is_big<<" "<<highscore<<"\n";

// Access a value that does not exist in the JSON data
    while(!window.get_is_done()){
    bool is_loading_saved_game = window.start_window();
    std::cout<<"czy wczytujemy: "<<is_loading_saved_game<<"\n";
    Game game(window, max_level);
    if(is_loading_saved_game)
    {
        game.load_game(level, lives, coins_earned_earlier, is_big);
    }

    while(!game.IsWindowDone() && !game.IsDone()){
        sf::Time elapsedTime = clock.restart();
        float delta_time = elapsedTime.asSeconds();
        game.GameUpdate(delta_time);
    }
    if(!window.get_is_done()){
    if(game.get_is_won())
    {
        int result = game.get_coins_earned_earlier();
        std::ifstream read_highscore_stream("data.json");
        read_highscore_stream>>data;
        highscore = data["highscore"];
        window.end_window_after_win(result, highscore);
    }
    else
    {
        window.end_window_after_lost();
    }
    }
    }
    //game.EndGame();
    return 0;
}