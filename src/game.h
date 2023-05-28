#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "window.h"
#include "tile_manager.h"
#include "ferdek.h"
#include "mob.h"
#include "mob_manager.h"
#include <memory>
#include "../libs/json.hpp"
#include <fstream>

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
        void GameAfterDeath();
        void GameUpdate(float time_warp);
        void EndGame();
        void ManagePlayerCollisions();
        void ManageMobsCollisions();
        bool IsDone();
        void MobsUpdate(float delta_time);
        bool IsWindowDone() const;
        void load_next_level();
        bool get_is_won() const;
        int get_coins_earned_earlier() const;
        void save_game() const;
};

#endif