#include "beer.h"

Beer::Beer()
{
    this->position = sf::Vector2f(0.f, 0.f);
    setup();

}

Beer::Beer(sf::Vector2f position)
{
    this->position = position;
    setup();
}
Beer::~Beer()
{
    
}

void Beer::setup()
{
    this->type = 1;
    this->texture.loadFromFile("src/imgs/Mocny_FULL.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
}

void Beer::mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big)
{
    if(std::pow(ferdek_position.x-position.x, 2) + std::pow(ferdek_position.y-position.y, 2) < 32.f*32.f)
    {
        marked_for_death = true;
        feedback = true;
    }
    else if(position.y > 16.5f*32)
    {
        marked_for_death = true;
    }
}
