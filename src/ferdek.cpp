#include "ferdek.h"
#include <iostream>
Ferdek::Ferdek() : position(sf::Vector2f(160.f, 480.f-128.f)), min_horizontal_warp(200),
max_horizontal_warp(600), acceleration_warp(1),  max_mini_jumps(15.f), is_big(false)
{
    texture_sheet.loadFromFile("src/imgs/Ferdek.png");
    left_warp = min_horizontal_warp;
    right_warp = min_horizontal_warp;
    faced_forward = true;
    sprite.setTexture(texture_sheet);
    sprite.setTextureRect(sf::IntRect(229, 0, 13, 16));
    sprite.setOrigin(0, 32);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(2.f, 2.f));
    left_collision = false;
    right_collision = false;
    top_collision = false;
    bottom_collision = false;
    is_jumping = false;
    mini_jumps = 0;
    gravity_warp = 300.f; //bylo 300
    mini_jump_height = 400.f; // domyslnie 400.f
    this->is_dead = false;
    //Reset();
}

Ferdek::~Ferdek()
{

}
void Ferdek::Reset()
{
    this->is_dead=false;
    this->position= sf::Vector2f(160.f, 480.f-128.f);
    this->is_big = false;
    left_warp = min_horizontal_warp;
    right_warp = min_horizontal_warp;
    faced_forward = true;
    sprite.setTextureRect(sf::IntRect(229, 0, 13, 16));
    sprite.setOrigin(0, 32);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(2.f, 2.f));
    left_collision = false;
    right_collision = false;
    top_collision = false;
    bottom_collision = false;
    is_jumping = false;
    mini_jumps = 0;
}

void Ferdek::Update(float time_warp)
{
    if(is_big){
    sprite.setColor(sf::Color(0, 255, 0));
    }
    else{
    sprite.setColor(sf::Color::White);

    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))&& !left_collision)
    {   
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
void Ferdek::SetIsBig(bool is_big)
{
    this->is_big = is_big;
}

void Ferdek::InstantKill()
{
    is_dead = true;
}
bool Ferdek::IsDead() const
{
    return is_dead;
}