#ifndef GAME_H
#define GAME_H
#include "window.h"
#include "tile_manager.h"
#include "mario.h"
class Game
{
    private:
        Window window;
        Mario mario;
        TileManager tile_manager;
        bool is_done;
    public:
        Game();
        ~Game();
        void GameSetup();
        void GameUpdate();
        void EndGame();
        void ManageMarioCollisionsAndGravity();
        bool IsDone();
};

#endif