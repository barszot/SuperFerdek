#include "ferdek.h"
#include <iostream>
Ferdek::Ferdek()

{

    // 0 - nic, 1 - bieg, 2 - skok, 3 - przykuc
    // faced_forward?, is_big?, akcja, klatka
    this->ferdek_texture_list[0][0][0][0] = sf::IntRect(6*16, 0, 16, 16);
    this->ferdek_texture_list[0][0][0][1] = sf::IntRect(7*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][1][0] = sf::IntRect(8*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][1][1] = sf::IntRect(9*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][2][0] = sf::IntRect(10*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][2][1] = sf::IntRect(10*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][3][0] = sf::IntRect(11*16,  0, 16, 16);
    this->ferdek_texture_list[0][0][3][1] = sf::IntRect(11*16,  0, 16, 16);

    this->ferdek_texture_list[0][1][0][0] = sf::IntRect(6*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][0][1] = sf::IntRect(7*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][1][0] = sf::IntRect(8*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][1][1] = sf::IntRect(9*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][2][0] = sf::IntRect(10*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][2][1] = sf::IntRect(10*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][3][0] = sf::IntRect(11*16, 16, 16, 32);
    this->ferdek_texture_list[0][1][3][1] = sf::IntRect(11*16, 16, 16, 32);

    this->ferdek_texture_list[1][0][0][0] = sf::IntRect(5*16, 0, 16, 16);
    this->ferdek_texture_list[1][0][0][1] = sf::IntRect(4*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][1][0] = sf::IntRect(3*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][1][1] = sf::IntRect(2*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][2][0] = sf::IntRect(1*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][2][1] = sf::IntRect(1*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][3][0] = sf::IntRect(0*16,  0, 16, 16);
    this->ferdek_texture_list[1][0][3][1] = sf::IntRect(0*16,  0, 16, 16);

    this->ferdek_texture_list[1][1][0][0] = sf::IntRect(5*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][0][1] = sf::IntRect(4*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][1][0] = sf::IntRect(3*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][1][1] = sf::IntRect(2*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][2][0] = sf::IntRect(1*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][2][1] = sf::IntRect(1*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][3][0] = sf::IntRect(0*16, 16, 16, 32);
    this->ferdek_texture_list[1][1][3][1] = sf::IntRect(0*16, 16, 16, 32);
    
    this->texture_sheet.loadFromFile("src/imgs/Ferdek.png");


    Reset();
}

Ferdek::~Ferdek()
{

}
void Ferdek::Reset()
{
    this->position = sf::Vector2f(160.f, 480.f-128.f);
    this->min_horizontal_warp = 200;
    this->max_horizontal_warp = 600;
    this->acceleration_warp = 1.f;
    this->max_mini_jumps=15.f;
    this->is_small_jump_heigth = 400.f;
    this->is_big_jump_heigth = 600.f;
    this->is_big=false;
    this->left_warp = min_horizontal_warp;
    this->right_warp = min_horizontal_warp;
    this->faced_forward = true;

    this->left_collision = false;
    this->right_collision = false;
    this->top_collision = false;
    this->bottom_collision = false;
    this->is_jumping = false;
    this->is_running = false;
    this->is_crouching = false;
    this->mini_jumps = 0;
    this->gravity_warp = 300.f; //bylo 300
    this->mini_jump_height = 400.f; // domyslnie 400.f
    this->is_dead = false;
    this->max_time_before_change = 0.3f;
    this->current_time_before_change = max_time_before_change;
    this->frame = false;
    this->sprite.setTexture(texture_sheet);
    this->sprite.setTextureRect(ferdek_texture_list[1][0][0][0]);
    this->sprite.setOrigin(0, 32);
    this->sprite.setPosition(position);
    this->sprite.setScale(sf::Vector2f(2.f, 2.f));
}

void Ferdek::Update(float time_warp)
{
    //std::cout<<left_collision<<" "<<right_collision<<" "<<top_collision<<" "<<bottom_collision<<"\n";
    current_time_before_change -= time_warp;
    if(current_time_before_change <= 0.f)
    {
        current_time_before_change = max_time_before_change;
        frame = !frame;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))&& !left_collision)
    {   
        is_running = true;
        if(faced_forward==true)
        {
            faced_forward = false;
            left_warp = min_horizontal_warp;
        }

        position.x -= left_warp*time_warp;
        sprite.setTextureRect(sf::IntRect(181, 0, 13, 16));
        left_warp = std::min(left_warp+acceleration_warp, max_horizontal_warp);

    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && !right_collision)
    {   
        is_running = true;
        if(faced_forward==false)
        {
            faced_forward = true;
            right_warp = min_horizontal_warp;
        }
        position.x += right_warp*time_warp;
        sprite.setTextureRect(sf::IntRect(229, 0, 13, 16));
        right_warp = std::min(right_warp+acceleration_warp, max_horizontal_warp);
    }
    else
    {
        is_running = false;
        right_warp = min_horizontal_warp;
        left_warp = min_horizontal_warp;

    }

    if(is_jumping)
    {
        position.y -= mini_jump_height*time_warp;
        DecrementMiniJumps(time_warp);
    }
    else if(!bottom_collision)
    {
        position.y +=  gravity_warp*time_warp;
    }

    sprite.setPosition(position);
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (!is_jumping && bottom_collision))
    {
        StartJumping();
    }
    if(top_collision)
    {   
        StopJumpingInstantly();
    }   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {   
        is_crouching = true;
    }
    else
    {
        is_crouching = false;
    }
    // 0 - nic, 1 - bieg, 2 - skok, 3 - przykuc
    // faced_forward?, is_big?, akcja, klatka
    int action = 0;
    if(is_crouching)
    {
        action = 3;
    }
    else if(is_jumping)
    {
        action = 2;
    }
    else if(is_running)
    {
        action = 1;
    }
    this->sprite.setTextureRect(ferdek_texture_list[!faced_forward][is_big][action][frame]);
    //std::cout<<is_big<<"  "<<32+32*is_big<<"\n";
}



const sf::Sprite& Ferdek::GetSprite() const
{
    return sprite;
}
const sf::Vector2f& Ferdek::GetPosition() const
{
    return position;
}

void Ferdek::SetY(const float& new_y)
{
    position.y = new_y;
}

bool Ferdek::IsJumping() const
{
    return is_jumping;
}
float Ferdek::GetMiniJump() const
{
    return mini_jump_height;
}
int Ferdek::GetNumberOfMiniJumps() const
{
    return mini_jumps;
}
void Ferdek::DecrementMiniJumps(float time_warp)
{
    //std::cout<<mini_jumps<<"\n";
    if(mini_jumps>0)
    {
        mini_jumps = std::max(0.f, mini_jumps - 100*time_warp);
    }
    if(mini_jumps==0)
    {
        is_jumping = false;
    }
}
void Ferdek::StartJumping()
{
    mini_jumps = max_mini_jumps;
    is_jumping = true;
}

void Ferdek::StopJumpingInstantly()
{
    mini_jumps = 0;
    is_jumping = false;
}


bool Ferdek::IsBig() const
{
    return is_big;
}
void Ferdek::SetIsBig(bool is_ferdek_big_now)
{   
    bool is_changed = !(is_ferdek_big_now==is_big);
    this->is_big = is_ferdek_big_now;
    if(is_changed){
        std::cout<<"prev position: "<<position.x<<" "<<position.y;
    if(is_big)
    {
        this->mini_jump_height = is_big_jump_heigth;
        this->sprite.setOrigin(0, 64);
        std::cout<<" curr position: "<<position.x<<" "<<position.y<<"\n";

        //std::cout<<"O KURDE\n";
    }
    else
    {
        this->mini_jump_height = is_small_jump_heigth;
        this->sprite.setOrigin(0, 32);

        std::cout<<" curr position: "<<position.x<<" "<<position.y<<"\n";

    }
    }
}

void Ferdek::InstantKill()
{
    is_dead = true;
}
bool Ferdek::IsDead() const
{
    return is_dead;
}