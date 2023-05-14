#include "mario.h"

Mario::Mario() : position(sf::Vector2f(64.f, 412.f)), min_horizontal_warp(2),
max_horizontal_warp(5), acceleration_warp(0.002)
{
    texture_sheet.loadFromFile("src/imgs/mario.png");
    left_warp = min_horizontal_warp;
    right_warp = min_horizontal_warp;
    faced_forward = true;
    sprite.setTexture(texture_sheet);
    sprite.setTextureRect(sf::IntRect(211, 0, 13, 16));
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(2.2f, 2.2f));
}

Mario::~Mario()
{

}

void Mario::Update()
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && position.x>min_horizontal_warp)
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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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


const sf::Sprite& Mario::GetSprite() const
{
    return sprite;
}
const sf::Vector2f& Mario::GetPosition() const
{
    return position;
}