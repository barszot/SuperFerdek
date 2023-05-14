#include "ferdek.h"
#include <iostream>
Ferdek::Ferdek() : position(sf::Vector2f(160.f, 480.f-64.f)), min_horizontal_warp(2),
max_horizontal_warp(6), acceleration_warp(0.01),  max_mini_jumps(45), mini_jump_height(2.01)
{
    texture_sheet.loadFromFile("src/imgs/mario.png");
    left_warp = min_horizontal_warp;
    right_warp = min_horizontal_warp;
    faced_forward = true;
    sprite.setTexture(texture_sheet);
    sprite.setTextureRect(sf::IntRect(211, 0, 13, 16));
    sprite.setOrigin(32, 32);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(2.f, 2.f));
    left_collision = false;
    right_collision = false;
    top_collision = false;
    bottom_collision = false;
    is_jumping = false;
    mini_jumps = 0;
}

Ferdek::~Ferdek()
{

}

void Ferdek::Update()
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))&& !left_collision)
    {   
        if(faced_forward==true)
        {
            faced_forward = false;
            left_warp = min_horizontal_warp;
        }

        position.x -= left_warp;
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
        position.x += right_warp;
        sprite.setTextureRect(sf::IntRect(211, 0, 13, 16));
        right_warp = std::min(right_warp+acceleration_warp, max_horizontal_warp);
    }
    else
    {
        right_warp = min_horizontal_warp;
        left_warp = min_horizontal_warp;

    }
    sprite.setPosition(position);
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (!is_jumping && bottom_collision))
    {
        StartJumping();
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
void Ferdek::DecrementMiniJumps()
{
    if(mini_jumps>0)
    {
        mini_jumps-=1;
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
