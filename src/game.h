#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "window.h"
#include "tile_manager.h"
#include "ferdek.h"
#include "mob.h"
#include <memory>
class Game
{
    private:
        Window& window;
        Ferdek ferdek;
        TileManager tile_manager;
        bool is_done;
        float gravity_warp;
        std::vector<std::shared_ptr<Mob>> mobs;
        unsigned int coins;
        int level;
        int lives;
    public:
        Game(Window& window);
        ~Game();
        void GameAfterDeath();
        void GameUpdate(float time_warp);
        void EndGame();
        void ManagePlayerCollisions();
        void ManageMobsCollisions();
        bool IsDone();
        void MobsUpdate(float delta_time);
        bool IsWindowDone() const;
};

#endif