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
    
    this->min_horizontal_warp = 200;
    this->max_horizontal_warp = 400;
    this->acceleration_warp = 4.f;
    this->max_mini_jumps=15.f;
    this->is_small_jump_heigth = 400.f;
    this->is_big_jump_heigth = 600.f;
    this->gravity_warp = 300.f; //bylo 300
    this->max_time_before_change = 0.3f;
    this->sprite.setTexture(texture_sheet);
    this->sprite.setScale(sf::Vector2f(2.f, 2.f));

    reset(true);
}

Ferdek::~Ferdek()
{

}
void Ferdek::reset(bool reset_completely)
{
    this->position = sf::Vector2f(160.f, 352.f);
    
    if(reset_completely){
    this->is_big=false;
    this->mini_jump_height = 400.f; // domyslnie 400.f
    }

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
    this->is_dead = false;
    this->current_time_before_change = max_time_before_change;
    this->frame = false;
    this->sprite.setTextureRect(ferdek_texture_list[faced_forward][is_big][0][0]);
    //this->sprite.setOrigin(0, 32);
    this->sprite.setPosition(position);
}

void Ferdek::update(float time_warp)
{
    //this->sprite.setOrigin(0, 32+32*is_big);

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



const sf::Sprite& Ferdek::get_sprite() const
{
    return sprite;
}
const sf::Vector2f& Ferdek::get_position() const
{
    return position;
}
void Ferdek::set_x(const float &new_x)
{
    position.x = new_x;
    sprite.setPosition(position);
}

void Ferdek::set_y(const float& new_y)
{
    position.y = new_y;
    sprite.setPosition(position);
}
void Ferdek::set_position(const sf::Vector2f& new_position)
{
    position = new_position;
    sprite.setPosition(new_position);
}
bool Ferdek::get_is_jumping() const
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
    is_crouching = false;
    mini_jumps = max_mini_jumps;
    is_jumping = true;
}

void Ferdek::StopJumpingInstantly()
{
    mini_jumps = 0;
    is_jumping = false;
}


bool Ferdek::get_is_big() const
{
    return is_big;
}
void Ferdek::set_is_big(bool is_ferdek_big_now)
{   
    this->is_big = is_ferdek_big_now;
    if(is_big)
    {
        this->mini_jump_height = is_big_jump_heigth;
    }
    else
    {
        this->mini_jump_height = is_small_jump_heigth;
    }
}

void Ferdek::instant_kill()
{
    is_dead = true;
}
bool Ferdek::get_is_dead() const
{
    return is_dead;
}
void Ferdek::set_sprite_origin(int x, int y)
{
    sprite.setOrigin(x, y);
}