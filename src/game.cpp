#include "game.h"

Game::Game(Window& window, int max_level): window(window), is_done(false), coins(0), coins_earned_earlier(0),  level(1),
lives(3), max_level(max_level), is_won(false), level_to_save(1), lives_to_save(3),
coins_earned_earlier_to_save(0), is_ferdek_big_to_save(false)
{
    this->mobs.clear();
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));
}

void Game::load_game(int current_level, int lives, int coins_earned_earlier, bool is_ferdek_big)
{

    this->level = current_level;
    this->lives = lives;
    this->coins_earned_earlier = coins_earned_earlier;
    this-> level_to_save = current_level;
    this-> lives_to_save = lives;
    this-> coins_earned_earlier = coins_earned_earlier;
    this->is_ferdek_big_to_save = is_ferdek_big;
    this->tile_manager.setup(level);
    this->mob_manager.setup(level);
    this->ferdek.set_is_big(is_ferdek_big);
    this->mobs.clear();
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));

}


Game::~Game() {}

void Game::game_after_death()
{
    this->ferdek.reset(true);
    this->tile_manager.setup(level);
    this->mobs.clear();
    mob_manager.setup(level);
    const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
    std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));
    this->coins = 0;

}

void Game::game_update(float delta_time)
{
        window.update();
        if(ferdek.get_is_dead()){
            lives -= 1;
            game_after_death();
        }
        if(lives<=0)
        {
            end_game();
            return;
        }
        delta_time = std::min(0.1f, delta_time);

        window.begin_draw();
        //tu narysuj tlo
        window.draw_tile_collection(tile_manager, int(ferdek.get_position().x)/32);
        window.draw_stats(coins+coins_earned_earlier, lives, level, ferdek.get_position().x, 0, tile_manager.get_length()*32);

        window.draw_mobs(mobs, ferdek.get_position().x);
        window.draw_ferdek(ferdek);


        window.update_view(ferdek.get_position().x, 0, tile_manager.get_length()*32);        
        ferdek.update(delta_time);
        mobs_update(delta_time);
        manage_ferdek_collisions();
        manage_mobs_collisions();
        window.end_draw();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            save_game();
        }


}

bool Game::get_is_done()
{
    return is_done;
}
void Game::end_game()
{
    is_done = true;
}
void Game::manage_ferdek_collisions()
{
    float x = ferdek.get_position().x;
    float y = ferdek.get_position().y;
    if(y>16.5f*32){
        ferdek.instant_kill();
        return;
    }
    int id_x = int(x) / 32;
    if(id_x>=tile_manager.get_length()-3)
    {
        load_next_level();
        return;
    }
    int id_x_special_1 = int(x + 8.f) / 32;
    int id_x_special_2 = int(x + 24.f) / 32;
    int id_y = (int(y) / 32) - 2;

    bool condition = ferdek.get_is_big() && !ferdek.is_crouching;

    if(tile_manager.check_tile(id_x+1,id_y) || tile_manager.check_tile(id_x+1,id_y-condition))
    {
        ferdek.right_collision = (!tile_manager.react_if_tile_is_coin(id_x+1,id_y, coins) || !tile_manager.react_if_tile_is_coin(id_x+1,id_y-condition, coins));

    }
    else
    {
        ferdek.right_collision = false;
    }
    if(tile_manager.check_tile(id_x,id_y) || tile_manager.check_tile(id_x,id_y-condition))
    {
        ferdek.left_collision = (!tile_manager.react_if_tile_is_coin(id_x,id_y, coins) || !tile_manager.react_if_tile_is_coin(id_x,id_y-condition, coins));
    }
    else
    {
        ferdek.left_collision = false;
    }
    if(tile_manager.check_tile(id_x_special_1,id_y+1) || tile_manager.check_tile(id_x_special_2,id_y+1))
    {
        ferdek.bottom_collision = !(tile_manager.react_if_tile_is_coin(id_x_special_1,id_y+1, coins) && tile_manager.react_if_tile_is_coin(id_x_special_2,id_y+1, coins));
        ferdek.set_y(32*(id_y+2));
    }
    else
    {
        ferdek.bottom_collision = false;
    }
    if(tile_manager.check_tile(id_x_special_1,id_y-condition) || tile_manager.check_tile(id_x_special_2,id_y-condition))
    {
        ferdek.top_collision = !(tile_manager.react_if_tile_is_coin(id_x_special_1,id_y-condition, coins) && tile_manager.react_if_tile_is_coin(id_x_special_2,id_y-condition, coins));

        auto mob_ptr_1 = tile_manager.tile_activation(id_x_special_1, id_y-condition);
        if(mob_ptr_1!=nullptr){
            mobs.push_back(mob_ptr_1);
        }

        if(id_x_special_1!=id_x_special_2){

            auto mob_ptr_2 = tile_manager.tile_activation(id_x_special_2, id_y-condition);
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
    if(id_x+2>=tile_manager.get_length())
    {
        ferdek.right_collision = true;
    }
    if(id_y - 1 <= 0)
    {
        ferdek.top_collision = true;

    }
}   

void Game::manage_mobs_collisions()
{

    int n = mobs.size();

    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek.get_position().x-mobs[i]->GetPosition().x)/32 < 24)
        {
            
            float x = mobs[i]->GetPosition().x;
            float y = mobs[i]->GetPosition().y;
            int id_x = int(x) / 32;
            int id_x_special_1 = int(x + 8.f) / 32;
            int id_x_special_2 = int(x + 24.f) / 32;
            int id_y = (int(y) / 32) - 2;
            if(id_x>=tile_manager.get_length()-3 || tile_manager.check_tile(id_x+1,id_y))
            {
                mobs[i]->SetFacedForward(false);

            }
            if(id_x-2 < 0 || tile_manager.check_tile(id_x,id_y))
            {
                mobs[i]->SetFacedForward(true);
            }
            if(tile_manager.check_tile(id_x_special_1,id_y+1) || tile_manager.check_tile(id_x_special_2,id_y+1))
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

void Game::mobs_update(float delta_time)
{
    int n = mobs.size();
    for(int i = 0; i<n;i++)
    {
        if (abs(ferdek.get_position().x-mobs[i]->GetPosition().x)/32 < 24)
        {
           mobs[i]->Update(delta_time);
        }
    }
}

bool Game::get_is_window_done() const
{
    return window.get_is_done();
}
void Game::load_next_level()
{
    this->level+=1;
    this->coins_earned_earlier += coins;
    this->level_to_save = level;
    this->coins_earned_earlier_to_save = coins_earned_earlier;
    this->lives_to_save = lives;
    this->is_ferdek_big_to_save = ferdek.get_is_big();
    if (level<=max_level)
    {
        this->coins = 0;
        tile_manager.load_next_level();
        mob_manager.load_next_level();
        ferdek.reset(false);
        this->tile_manager.setup(level);
        this->mobs.clear();
        const std::vector<std::shared_ptr<Mob>>& primary_mobs = mob_manager.get_mobs();
        std::copy(primary_mobs.begin(), primary_mobs.end(), std::back_inserter(mobs));
    }
    else
    {   
        nlohmann::json prev_data;
        std::ifstream read_highscore_to_update_stream("data.json");
        read_highscore_to_update_stream>>prev_data;
        int highscore = prev_data["highscore"];
        if(coins_earned_earlier>highscore)
        {
            nlohmann::json new_data;
            new_data["coins_earned_earlier"] = prev_data["coins_earned_earlier"];
            new_data["is_big"] = prev_data["is_big"];
            new_data["level"] = prev_data["level"];
            new_data["lives"] = prev_data["lives"];
            new_data["highscore"] = coins_earned_earlier;
            std::ofstream save_highscore_to_update_stream("data.json");
            save_highscore_to_update_stream << new_data << std::endl;
        }

        
        is_done = true;
        is_won = true;
    }
}

bool Game::get_is_won() const
{
    return is_won;
}
int Game::get_coins_earned_earlier() const
{
    return coins_earned_earlier;
}
void Game::save_game() const
{
    std::ifstream save_game_read_stream("data.json");
    nlohmann::json prev_data;
    save_game_read_stream >> prev_data;
    int highscore = prev_data["highscore"];
    nlohmann::json new_data;
    new_data["coins_earned_earlier"] = coins_earned_earlier_to_save;
    new_data["highscore"] = highscore;
    new_data["is_big"] = is_ferdek_big_to_save;
    new_data["level"] = level_to_save;
    new_data["lives"] = lives_to_save;
    std::ofstream save_game_load_stream("data.json");
    save_game_load_stream << new_data << std::endl;
}