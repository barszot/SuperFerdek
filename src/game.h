#ifndef GAME_H
#define GAME_H
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
        void GameUpdate();
        void EndGame();
        void ManagePlayerCollisions();
        bool IsDone();
};

#endif