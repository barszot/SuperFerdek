#include "game.h"
#include <iostream>
Game::Game() : window(Window("Super Ferdek", sf::Vector2u(1024, 512))), is_done(false) {}

Game::~Game() {}

void Game::GameSetup()
{

}

void Game::GameUpdate()
{
        if(window.IsDone()){
            EndGame();
            return;
        }
        window.BeginDraw();
        window.DrawTileCollection(tile_manager);
        window.Draw(ferdek.GetSprite());
        window.UpdateView(ferdek.GetPosition().x, 0, 16384);
        window.Update();
        ferdek.Update();
        ManagePlayerCollisions();
        window.EndDraw();
}

bool Game::IsDone()
{
    return is_done;
}
void Game::EndGame()
{
    is_done = true;
    window.Destroy();
}
void Game::ManagePlayerCollisions()
{
    const std::vector<std::vector<int>>& tile_types = tile_manager.GetTileTypes();
    float x = ferdek.GetPosition().x;
    float y = ferdek.GetPosition().y;
    int id_x = int(x) / 32 - 1;
    int id_y = (int(y) / 32) - 2;
    //std::cout<<id_x<<" "<<id_y<<" "<<tile_types[id_x][id_y]<<"\n";
    if(tile_types[id_x][id_y]>=0)
    {
        ferdek.right_collision = true;
    }
    else
    {
        ferdek.right_collision = false;
    }
    if(id_x-2 < 0 || tile_types[id_x-2][id_y]>=0 )
    {
        ferdek.left_collision = true;
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_types[id_x-1][id_y-1]>=0)
    {
        ferdek.bottom_collision = true;
    }
    else
    {
        ferdek.bottom_collision = false;
    }

}   
