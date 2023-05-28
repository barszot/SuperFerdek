#include "mob.h"

Mob::Mob()
{
    this->faced_forward = true;
    this->speed = 200.f;
    this->gravity_speed = 300.f;
    this->bottom_collision = false;
    this->marked_for_death = false;
    this->feedback = false;
}
Mob::~Mob()
{

}

bool Mob::get_is_faced_forward() const
{
    return faced_forward;
}
float Mob::get_speed() const
{
    return speed;
}
void Mob::toggle_faced_forward()
{
    faced_forward = !(faced_forward);
}
sf::Vector2f Mob::get_position() const
{
    return position;
}
sf::Sprite Mob::get_sprite() const
{
    return sprite;
}
void Mob::update(float delta_time)
{
    move(delta_time);
}
void Mob::move(float delta_time)
{
    if(bottom_collision)
    {
        if(faced_forward)
        {
            position.x += delta_time*speed;
        }
        else
        {
            position.x -= delta_time*speed;
        }
    }
    else
    {
        position.y += delta_time*gravity_speed;
    }
    sprite.setPosition(position);
}
bool Mob::get_bottom_collision() const
{
    return bottom_collision;
}
void Mob::toggle_bottom_collision()
{
    bottom_collision = !(bottom_collision);
}
void Mob::set_bottom_collision(bool new_bottom_collision)
{
    bottom_collision = new_bottom_collision;
}

void Mob::set_faced_forward(bool new_faced_forward)
{
    faced_forward = new_faced_forward;
}

void Mob::set_y(float new_y)
{
    position.y = new_y;
    sprite.setPosition(position);
}

void Mob::set_marked_for_death(bool is_marked)
{
    marked_for_death = is_marked;
}

bool Mob::get_marked_for_death() const
{
    return marked_for_death;
}
void Mob::mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big)
{

}
bool Mob::get_feedback() const
{
    return feedback;
}

int Mob::get_type() const
{
    return type;
}
