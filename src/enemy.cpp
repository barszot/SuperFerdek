#include "enemy.h"

Enemy::Enemy()
{
    Mob();
    this->current_time_of_not_killing_ferdek=0.f;
    this->max_time_of_not_killing_ferdek=1.f;
    this->can_kill_ferdek=true;
}
Enemy::~Enemy()
{

}
void Enemy::update(float delta_time)
{
    move(delta_time);
    if(current_time_of_not_killing_ferdek>0.f)
    {
        current_time_of_not_killing_ferdek -= delta_time;
    }
    if(current_time_of_not_killing_ferdek<=0.f)
    {
        can_kill_ferdek = true;
    }
}

bool Enemy::get_can_kill_ferdek() const
{
    return can_kill_ferdek;
}

void Enemy::check_if_kills_ferdek(sf::Vector2f ferdek_position)
{

}
