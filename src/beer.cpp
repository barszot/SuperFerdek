#include "beer.h"

Beer::Beer()
{
    Setup();

}

Beer::Beer(sf::Vector2f position)
{
    this->position = position;
    Setup();
}
Beer::~Beer()
{
    
}

void Beer::Setup()
{
    this->texture.loadFromFile("src/imgs/Mocny_FULL.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
    //this->speed = 0.1f;
    //this->gravity_speed = 10.f;
}

void Beer::MarkForDeathIfNecessary(sf::Vector2f ferdek_position)
{
    if(std::pow(ferdek_position.x-position.x, 2) + std::pow(ferdek_position.y-position.y, 2) < 32.f*32.f)
    {
        marked_for_death = true;
        feedback = true;
    }
    else if(position.y > 16.f*32)
    {
        marked_for_death = true;
    }
}
