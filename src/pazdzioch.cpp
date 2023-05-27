#include "pazdzioch.h"

Pazdzioch::Pazdzioch()
{

    this->position = sf::Vector2f(0.f, 0.f);
    setup();

}
Pazdzioch::Pazdzioch(sf::Vector2f position)
{
    this->position = position;
    setup();
}
Pazdzioch::~Pazdzioch()
{

}
void Pazdzioch::setup()
{
    this->type = -1;
    this->texture.loadFromFile("src/imgs/pazdzioch.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
    this->speed = 100.f;
}
void Pazdzioch::MarkForDeathIfNecessary(sf::Vector2f ferdek_position, bool is_ferdek_big)
{

    if(abs(ferdek_position.x - position.x)<16.f && (abs(ferdek_position.y-position.y)<=40.f && abs(ferdek_position.y-position.y) > 24.f))
    {
        marked_for_death = true;
    }

    else if(position.y > 16.f*32)
    {
        marked_for_death = true;
    }
    else if(std::pow(ferdek_position.x-position.x, 2) + std::pow(ferdek_position.y-position.y, 2) < 32.f*32.f)
    {   
        marked_for_death = false;
        feedback = (can_kill_ferdek && !marked_for_death);
        if(is_ferdek_big && feedback)
        {
            can_kill_ferdek = false;
            current_time_of_not_killing_ferdek = max_time_of_not_killing_ferdek;
        }
    }
}