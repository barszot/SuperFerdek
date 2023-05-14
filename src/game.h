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
    public:
        Game();
        ~Game();
        void GameSetup();
        void GameUpdate();
        void EndGame();
        void ManagePlayerCollisionsAndGravity();
        bool IsDone();
};

#endif