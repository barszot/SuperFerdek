#include "game.h"
#include "beer.h"
#include "spark.h"
#include <iostream>
#include "enemy.h"
#include "pazdzioch.h"
#include <memory>
Game::Game(Window& window, int max_level): window(window), is_done(false), gravity_speed(250.f), coins(0), coins_earned_earlier(0),  level(1),
lives(3), max_level(max_level), is_won(false)
{
    //sf::Time duration = sf::seconds(0.5f); // Tworzenie obiektu sf::Time o długości 0.5 sekundy
    //::sleep(duration); // Użycie sf::sleep do zatrzymania programu na określony czas
    mobs.clear();
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));

    //mobs.push_back(std::make_shared<Pazdzioch>(sf::Vector2f(420.f, 480.f)));
}

Game::Game(Window& window, int max_level, int current_level, int lives, unsigned int coins_earned_earlier, bool is_ferdek_big): window(window),
is_done(false), gravity_speed(250.f), coins(0), coins_earned_earlier(coins_earned_earlier), level(current_level), lives(lives), max_level(max_level), is_won(false)
{
    tile_manager.Setup(level);
    mob_manager.setup(level);
    ferdek.set_is_big(true);
    std::cout<<"cyz ferdek jest wielki? "<<ferdek.get_is_big()<<"\n";
    mobs.clear();
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));

}


Game::~Game() {}

void Game::GameAfterDeath()
{
    this->ferdek.reset(true);
    this->tile_manager.Setup(level);
    this->mobs.clear();
    mob_manager.setup(level);
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));
    //std::cout<<"MOBS: "<<mobs.size()<<"\n";
    this->coins = 0;
    //mobs.push_back(std::make_shared<Pazdzioch>(sf::Vector2f(420.f, 480.f)));

}

void Game::GameUpdate(float time_warp)
{
        window.update();
        if(ferdek.get_is_dead()){
            lives -= 1;
            GameAfterDeath();
        }
        if(lives<=0)
        {
            EndGame();
            return;
        }
        time_warp = std::min(0.1f, time_warp);

        window.begin_draw();
        //tu narysuj tlo

        window.draw_tile_collection(tile_manager, int(ferdek.get_position().x)/32);
        window.draw_stats(coins+coins_earned_earlier, lives, level, ferdek.get_position().x, 0, tile_manager.GetLength()*32);

        window.draw_mobs(mobs, ferdek.get_position().x);
        window.draw_ferdek(ferdek);


        window.update_view(ferdek.get_position().x, 0, tile_manager.GetLength()*32);        
        ferdek.update(time_warp);
        MobsUpdate(time_warp);
        ManagePlayerCollisions();
        ManageMobsCollisions();
        window.end_draw();
}

bool Game::IsDone()
{
    return is_done;
}
void Game::EndGame()
{
    is_done = true;
}
void Game::ManagePlayerCollisions()
{
    float x = ferdek.get_position().x;
    float y = ferdek.get_position().y;
    if(y>16.5f*32){ //oryginalnie 16.5f * 32
        ferdek.instant_kill();
        return;
    }
    int id_x = int(x) / 32;
    //std::cout<<id_x<<" "<<tile_manager.GetLength()<<"\n";
    if(id_x>=tile_manager.GetLength()-3)
    {
        load_next_level();
        return;
    }
    int id_x_special_1 = int(x + 8.f) / 32;
    int id_x_special_2 = int(x + 24.f) / 32;
    int id_y = (int(y) / 32) - 2;

    bool condition = ferdek.get_is_big() && !ferdek.is_crouching;

    //std::cout<<tile_types[id_x_special_1][id_y]<<" "<<tile_types[id_x_special_2][id_y]<<"\n";
    if(tile_manager.CheckTile(id_x+1,id_y) || tile_manager.CheckTile(id_x+1,id_y-condition))
    {
        ferdek.right_collision = (!tile_manager.ReactIfTileIsCoin(id_x+1,id_y, coins) || !tile_manager.ReactIfTileIsCoin(id_x+1,id_y-condition, coins));

    }
    else
    {
        ferdek.right_collision = false;
    }
    if(tile_manager.CheckTile(id_x,id_y) || tile_manager.CheckTile(id_x,id_y-condition))
    {
        ferdek.left_collision = (!tile_manager.ReactIfTileIsCoin(id_x,id_y, coins) || !tile_manager.ReactIfTileIsCoin(id_x,id_y-condition, coins));
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y+1) || tile_manager.CheckTile(id_x_special_2,id_y+1))
    {
        ferdek.bottom_collision = !(tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y+1, coins) && tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y+1, coins));

        //std::cout<<tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y+1, coins)<<" "<<tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y+1, coins)<<"\n";
        ferdek.set_y(32*(id_y+2));
    }
    else
    {
        ferdek.bottom_collision = false;
    }
    if(tile_manager.CheckTile(id_x_special_1,id_y-condition) || tile_manager.CheckTile(id_x_special_2,id_y-condition))
    {
        ferdek.top_collision = !(tile_manager.ReactIfTileIsCoin(id_x_special_1,id_y-condition, coins) && tile_manager.ReactIfTileIsCoin(id_x_special_2,id_y-condition, coins));

        auto mob_ptr_1 = tile_manager.TileActivation(id_x_special_1, id_y-condition);
        if(mob_ptr_1!=nullptr){
            mobs.push_back(mob_ptr_1);
        }

        if(id_x_special_1!=id_x_special_2){

            auto mob_ptr_2 = tile_manager.TileActivation(id_x_special_2, id_y-condition);
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
    if(id_x-2<0)
    {
        ferdek.left_collision = true;
    }
    if(id_x+2>=tile_manager.GetLength())
    {
        ferdek.right_collision = true;
    }
    if(id_y - 1 <= 0)
    {
        ferdek.top_collision = true;

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
        //std::cout<<i<<" "<<mobs[i]->GetType()<<"\n";
        if (abs(ferdek.get_position().x-mobs[i]->GetPosition().x)/32 < 24)
        {
            
            float x = mobs[i]->GetPosition().x;
            float y = mobs[i]->GetPosition().y;
            int id_x = int(x) / 32;
            int id_x_special_1 = int(x + 8.f) / 32;
            int id_x_special_2 = int(x + 24.f) / 32;
            int id_y = (int(y) / 32) - 2;
            if(id_x>=tile_manager.GetLength()-3 || tile_manager.CheckTile(id_x+1,id_y))
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

            mobs[i]->MarkForDeathIfNecessary(ferdek.get_position(), ferdek.get_is_big());
            if(mobs[i]->GetFeedback() && mobs[i]->GetType()<0)
            {
                ferdek.not_instant_kill();
            }
            ferdek.set_is_big(ferdek.get_is_big() || (mobs[i]->GetFeedback() && mobs[i]->GetType() == 1));
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
        if (abs(ferdek.get_position().x-mobs[i]->GetPosition().x)/32 < 24)
        {
           mobs[i]->Update(delta_time);
        }
    }
}

bool Game::IsWindowDone() const
{
    return window.get_is_done();
}
void Game::load_next_level()
{
    this->level+=1;
    this->coins_earned_earlier += coins;
    if (level<=max_level)
    {
        this->coins = 0;
        tile_manager.load_next_level();
        mob_manager.load_next_level();
        ferdek.reset(false);
        this->tile_manager.Setup(level);
        this->mobs.clear();
        const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
        std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));
    }
    else
    {      
        is_done = true;
        is_won = true;
    }
}

bool Game::get_is_won() const
{
    return is_won;
}
unsigned int Game::get_coins_earned_earlier() const
{
    return coins_earned_earlier;
}
