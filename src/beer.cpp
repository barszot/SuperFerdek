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
    this->texture.loadFromFile("src/imgs/beer_texture.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
    //this->speed = 0.1f;
    //this->gravity_speed = 10.f;
}