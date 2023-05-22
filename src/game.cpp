#include "game.h"
#include "beer.h"
#include "spark.h"
#include <iostream>
Game::Game() : window(Window("Super Ferdek", sf::Vector2u(1024, 512))), is_done(false), gravity_warp(250.f), coins(0), level(1), lives(3)
{
    //sf::Time duration = sf::seconds(0.5f); // Tworzenie obiektu sf::Time o długości 0.5 sekundy
    //::sleep(duration); // Użycie sf::sleep do zatrzymania programu na określony czas
    mobs.clear();
    //mobs.push_back(std::make_shared<Spark>(sf::Vector2f(420.f, 480.f)));
}

Game::~Game() {}

void Game::GameAfterDeath()
{
    this->ferdek.Reset();
    this->tile_manager.Setup(level);
    this->mobs.clear();
    this->coins = 0;

}

void Game::GameUpdate(float time_warp)
{
        window.Update();
        if(ferdek.IsDead()){
            lives -= 1;
            std::cout<<"RESET\n";
            GameAfterDeath();
        }
        if(lives<=0)
        {
            EndGame();
            return;
        }
        time_warp = std::min(0.1f, time_warp);

        window.BeginDraw();
        //tu narysuj tlo
        window.DrawStats(coins, lives, ferdek.GetPosition().x, 0, 16384);

        window.DrawTileCollection(tile_manager, int(ferdek.GetPosition().x)/32);
        window.DrawMobs(mobs, ferdek.GetPosition().x);
        window.Draw(ferdek.GetSprite());
        window.UpdateView(ferdek.GetPosition().x, 0, 16384);        
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
    if(y>16.5f*32){
        ferdek.InstantKill();
    }
    int id_x = int(x) / 32;
    int id_x_special_1 = int(x + 8.f) / 32;
    int id_x_special_2 = int(x + 24.f) / 32;
    int id_y = (int(y) / 32) - 2;

    //std::cout<<tile_types[id_x_special_1][id_y]<<" "<<tile_types[id_x_special_2][id_y]<<"\n";
    if(tile_manager.CheckTile(id_x+1,id_y))
    {
        ferdek.right_collision = !tile_manager.ReactIfTileIsCoin(id_x+1,id_y, coins);

    }
    else
    {
        ferdek.right_collision = false;
    }
    if(id_x-2 < 0 || tile_manager.CheckTile(id_x,id_y))
    {
        ferdek.left_collision = !tile_manager.ReactIfTileIsCoin(id_x,id_y, coins);
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y+1) || tile_manager.CheckTile(id_x_special_2,id_y+1))
    {
        ferdek.bottom_collision = !(tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y+1, coins) && tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y+1, coins));

        //std::cout<<tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y+1, coins)<<" "<<tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y+1, coins)<<"\n";
        ferdek.SetY(32*(id_y+2));
    }
    else
    {
        ferdek.bottom_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y) || tile_manager.CheckTile(id_x_special_2,id_y))
    {
        ferdek.top_collision = !(tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y, coins) && tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y, coins));

        auto mob_ptr_1 = tile_manager.TileActivation(id_x_special_1, id_y);
        if(mob_ptr_1!=nullptr){
            mobs.push_back(mob_ptr_1);
        }

        if(id_x_special_1!=id_x_special_2){

            auto mob_ptr_2 = tile_manager.TileActivation(id_x_special_2, id_y);
            if(mob_ptr_2!=nullptr)
            {
                mobs.push_back(mob_ptr_2);
            }
        }

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
            mobs[i]->MarkForDeathIfNecessary(ferdek.GetPosition());
            ferdek.SetIsBig(ferdek.IsBig() || (mobs[i]->GetFeedback()&&mobs[i]->GetType() == 1));
            coins += (mobs[i]->GetFeedback()&&mobs[i]->GetType() == 2);
        }
    }
    mobs.erase(std::remove_if(mobs.begin(), mobs.end(),
        [](const std::shared_ptr<Mob>& mob_ptr) {
            
            return (mob_ptr->GetMarkedForDeath());
        }), mobs.end());
}

void Game::MobsUpdate(float delta_time)
{
    int n = mobs.size();
    //std::cout<<n<<"\n";
    for(int i = 0; i<n;i++)
    {
        //std::cout<<i<<" "<<mobs[i]->GetSpeed()<<std::endl;
        if (abs(ferdek.GetPosition().x-mobs[i]->GetPosition().x)/32 < 24)
        {
           mobs[i]->Update(delta_time);
        }
    }
}

bool Game::IsWindowDone() const
{
    return window.IsDone();
}
