#include "ferdek.h"

Ferdek::Ferdek() : position(sf::Vector2f(64.f, 480.f)), min_horizontal_warp(2),
max_horizontal_warp(6), acceleration_warp(0.01)
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
}

Ferdek::~Ferdek()
{

}

void Ferdek::Update()
{
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && position.x>left_warp+64) && !left_collision)
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
        faced_forward = true;
        right_warp = std::min(right_warp+acceleration_warp, max_horizontal_warp);
    }

    sprite.setPosition(position);

}


const sf::Sprite& Ferdek::GetSprite() const
{
    return sprite;
}
const sf::Vector2f& Ferdek::GetPosition() const
{
    return position;
}