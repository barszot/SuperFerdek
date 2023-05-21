#include "game.h"
#include "beer.h"
#include <iostream>
Game::Game() : window(Window("Super Ferdek", sf::Vector2u(1024, 512))), is_done(false), gravity_warp(250.f)
{
    //sf::Time duration = sf::seconds(0.5f); // Tworzenie obiektu sf::Time o długości 0.5 sekundy
    //::sleep(duration); // Użycie sf::sleep do zatrzymania programu na określony czas
    mobs.clear();
    mobs.push_back(std::make_shared<Beer>(sf::Vector2f(384.f, 480.f)));
}

Game::~Game() {}

void Game::GameSetup()
{

}

void Game::GameUpdate(float time_warp)
{
        std::cout<<time_warp<<"\n";
        if(window.IsDone() || ferdek.GetPosition().y>16.5f*32){
            EndGame();
            return;
        }
        window.BeginDraw();
        window.DrawTileCollection(tile_manager, int(ferdek.GetPosition().x)/32);
        window.DrawMobs(mobs, ferdek.GetPosition().x);
        window.Draw(ferdek.GetSprite());
        window.UpdateView(ferdek.GetPosition().x, 0, 16384);
        window.Update();
        ferdek.Update(time_warp);
        MobsUpdate(time_warp);
        ManagePlayerCollisions();
        ManageMobsCollisions();
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
    float x = ferdek.GetPosition().x;
    float y = ferdek.GetPosition().y;
    int id_x = int(x) / 32;
    int id_x_special_1 = int(x + 8.f) / 32;
    int id_x_special_2 = int(x + 24.f) / 32;
    int id_y = (int(y) / 32) - 2;

    //std::cout<<tile_types[id_x_special_1][id_y]<<" "<<tile_types[id_x_special_2][id_y]<<"\n";
    if(tile_manager.CheckTile(id_x+1,id_y))
    {
        ferdek.right_collision = true;

    }
    else
    {
        ferdek.right_collision = false;
    }
    if(id_x-2 < 0 || tile_manager.CheckTile(id_x,id_y))
    {
        ferdek.left_collision = true;
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y+1) || tile_manager.CheckTile(id_x_special_2,id_y+1))
    {
        ferdek.bottom_collision = true;


        //std::cout<<y<<" "<<32*(id_y+2)<<"\n";
        ferdek.SetY(32*(id_y+2));
    }
    else
    {
        ferdek.bottom_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y) || tile_manager.CheckTile(id_x_special_2,id_y))
    {
        ferdek.top_collision = true;

        tile_manager.TileActivation(id_x_special_1, id_y, false);
        tile_manager.TileActivation(id_x_special_2, id_y, false);
    }
    else
    {
        ferdek.top_collision = false;
    }
    

    //std::cout<<ferdek.bottom_collision<<"\n";
}   

void Game::ManageMobsCollisions()
{

    int n = mobs.size();
    //std::cout<<n<<"\n";
    //std::cout<<mobs[0]<<"\n";
    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek.GetPosition().x-mobs[i]->GetPosition().x)/32 < 24)
        {
            
            float x = mobs[i]->GetPosition().x;
            float y = mobs[i]->GetPosition().y;
            int id_x = int(x) / 32;
            int id_x_special_1 = int(x + 8.f) / 32;
            int id_x_special_2 = int(x + 24.f) / 32;
            int id_y = (int(y) / 32) - 2;
            if(tile_manager.CheckTile(id_x+1,id_y))
            {
                mobs[i]->SetFacedForward(false);

            }
            if(id_x-2 < 0 || tile_manager.CheckTile(id_x,id_y))
            {
                mobs[i]->SetFacedForward(true);
            }
            if(tile_manager.CheckTile(id_x_special_1,id_y+1) || tile_manager.CheckTile(id_x_special_2,id_y+1))
            {
                mobs[i]->SetBottomCollision(true);
                mobs[i]->SetY(32*(id_y+2));
            }
            else
            {
                mobs[i]->SetBottomCollision(false);
            }
        }
    }
    mobs.erase(std::remove_if(mobs.begin(), mobs.end(),
        [](const std::shared_ptr<Mob>& mobPtr) {
            
            return (mobPtr->GetPosition().y > 17*32);
        }), mobs.end());
}

void Game::MobsUpdate(float delta_time)
{
    int n = mobs.size();
    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek.GetPosition().x-mobs[i]->GetPosition().x)/32 < 24)
        {
           mobs[i]->Update(delta_time);
        }
    }
}
