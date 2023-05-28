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
    nlohmann::json data = nlohmann::json::parse(f);
    int level = std::stoi(data.value("level", "1"));
    int lives = std::stoi(data.value("lives", "3"));
    int coins_earned_earlier = std::stoi(data.value("coins_earned_earlier", "0"));
    bool is_big = std::stoi(data.value("is_big", "0"));
// Access a value that does not exist in the JSON data
    std::cout<<"json test: "<<level<<" "<<lives<<" "<<coins_earned_earlier<<" "<<is_big<<"\n";
    while(!window.get_is_done()){
    bool is_loading_saved_game = window.start_window();
    std::cout<<"czy wczytujemy: "<<is_loading_saved_game<<"\n";
    if(is_loading_saved_game)
    {
        Game game(window, max_level, level, lives, coins_earned_earlier, is_big);
    }
    else
    {
        Game game(window, max_level);
    }
    Game game(window, max_level);
    while(!game.IsWindowDone() && !game.IsDone()){
        sf::Time elapsedTime = clock.restart();
        float delta_time = elapsedTime.asSeconds();
        game.GameUpdate(delta_time);
    }
    if(!window.get_is_done()){
    if(game.get_is_won())
    {
        unsigned int result = game.get_coins_earned_earlier();
        window.end_window_after_win(result);
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