#include "game.h"
#include <iostream>
Game::Game() : window(Window("Super Ferdek", sf::Vector2u(1024, 512))), is_done(false), gravity_warp(250.f)
{
    //sf::Time duration = sf::seconds(0.5f); // Tworzenie obiektu sf::Time o długości 0.5 sekundy
    //::sleep(duration); // Użycie sf::sleep do zatrzymania programu na określony czas
    
}

Game::~Game() {}

void Game::GameSetup()
{

}

void Game::GameUpdate(float time_warp)
{
        if(window.IsDone() || ferdek.GetPosition().y>16.5f*32){
            EndGame();
            return;
        }
        window.BeginDraw();
        window.DrawTileCollection(tile_manager);
        window.Draw(ferdek.GetSprite());
        window.UpdateView(ferdek.GetPosition().x, 0, 16384);
        window.Update();
        ferdek.Update(time_warp);
        ManagePlayerCollisions(time_warp);
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
void Game::ManagePlayerCollisions(float time_warp)
{
    const std::vector<std::vector<int>>& tile_types = tile_manager.GetTileTypes();
    float x = ferdek.GetPosition().x;
    float y = ferdek.GetPosition().y;
    int id_x = int(x) / 32;
    int id_x_special_1 = int(x + 8.f) / 32;
    int id_x_special_2 = int(x + 24.f) / 32;
    int id_y = (int(y) / 32) - 2;

    //std::cout<<tile_types[id_x_special_1][id_y]<<" "<<tile_types[id_x_special_2][id_y]<<"\n";
    if(tile_types[id_x+1][id_y]>=0)
    {
        ferdek.right_collision = true;
    }
    else
    {
        ferdek.right_collision = false;
    }
    if(id_x-2 < 0 || tile_types[id_x][id_y]>=0 )
    {
        ferdek.left_collision = true;
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_types[id_x_special_1][id_y+1] >=0 || tile_types[id_x_special_2][id_y+1] >= 0)
    {
        ferdek.bottom_collision = true;
        //std::cout<<y<<" "<<32*(id_y+2)<<"\n";
        ferdek.SetY(32*(id_y+2));
    }
    else
    {
        ferdek.bottom_collision = false;
    }
    if(tile_types[id_x_special_1][id_y] >=0 || tile_types[id_x_special_2][id_y]>=0)
    {
        ferdek.top_collision = true;
    }
    else
    {
        ferdek.top_collision = false;
    }
    

    //std::cout<<ferdek.bottom_collision<<"\n";
}   

