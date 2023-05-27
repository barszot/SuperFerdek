#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "window.h"
#include "tile_manager.h"
#include "ferdek.h"
#include "mob.h"
#include "mob_manager.h"
#include <memory>
class Game
{
    private:
        Window& window;
        Ferdek ferdek;
        TileManager tile_manager;
        MobManager mob_manager;
        bool is_done;
        float gravity_speed;
        std::vector<std::shared_ptr<Mob>> mobs;
        unsigned int coins;
        unsigned int coins_earned_earlier;
        int level;
        int lives;
        const int max_level;
        bool is_won;
    public:
        Game(Window& window, int max_level);
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
        unsigned int get_coins_earned_earlier() const;
};

#endif