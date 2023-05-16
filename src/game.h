#ifndef GAME_H
#define GAME_H
#include <cmath>
#include "window.h"
#include "tile_manager.h"
#include "ferdek.h"
class Game
{
    private:
        Window window;
        Ferdek ferdek;
        TileManager tile_manager;
        bool is_done;
        float gravity_warp;
    public:
        Game();
        ~Game();
        void GameSetup();
        void GameUpdate(float time_warp);
        void EndGame();
        void ManagePlayerCollisions(float time_warp);
        bool IsDone();
};

#endif