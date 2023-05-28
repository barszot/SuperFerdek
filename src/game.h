#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "window.h"
#include "tile_manager.h"
#include "ferdek.h"
#include "mob.h"
#include "mob_manager.h"
#include "../libs/json.hpp"
#include <fstream>
#include <memory>
#include "beer.h"
#include "spark.h"
#include "enemy.h"
#include "pazdzioch.h"
class Game
{
    private:
        Window& window;
        Ferdek ferdek;
        TileManager tile_manager;
        MobManager mob_manager;
        bool is_done;
        std::vector<std::shared_ptr<Mob>> mobs;
        int coins;
        int coins_earned_earlier;
        int level;
        int lives;
        const int max_level;
        bool is_won;
        int level_to_save;
        int lives_to_save;
        int coins_earned_earlier_to_save;
        bool is_ferdek_big_to_save;

    public:
        Game(Window& window, int max_level);
        void load_game(int current_level, int lives, int coins_earned_earlier, bool is_ferdek_big);
        ~Game();
        void game_after_death();
        void game_update(float delta_time);
        void end_game();
        void manage_ferdek_collisions();
        void manage_mobs_collisions();
        bool get_is_done();
        void mobs_update(float delta_time);
        bool get_is_window_done() const;
        void load_next_level();
        bool get_is_won() const;
        int get_coins_earned_earlier() const;
        void save_game() const;
};

#endif