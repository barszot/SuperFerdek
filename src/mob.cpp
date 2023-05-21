#include "mob.h"

Mob::Mob()
{
    this->faced_forward = true;
    this->speed = 200.f;
    this->gravity_speed = 300.f;
    this->bottom_collision = false;

}
Mob::~Mob()
{

}

bool Mob::IsFacedForward() const
{
    return faced_forward;
}
float Mob::GetSpeed() const
{
    return speed;
}
void Mob::ToggleFacedForward()
{
    faced_forward = !(faced_forward);
}
sf::Vector2f Mob::GetPosition() const
{
    return position;
}
sf::Sprite Mob::GetSprite() const
{
    return sprite;
}
void Mob::Update(float delta_time)
{
    Move(delta_time);
}
void Mob::Move(float delta_time)
{
    if(faced_forward)
    {
        position.x += std::min(delta_time*speed, 2.f);
    }
    else
    {
        position.x -= std::min(delta_time*speed, 2.f);
    }
    if(!bottom_collision)
    {
        position.y += std::min(delta_time*gravity_speed, 2.f);
    }
    sprite.setPosition(position);
}
bool Mob::GetBottomCollision() const
{
    return bottom_collision;
}
void Mob::ToggleBottomCollision()
{
    bottom_collision = !(bottom_collision);
}
void Mob::SetBottomCollision(bool new_bottom_collision)
{
    bottom_collision = new_bottom_collision;
}

void Mob::SetFacedForward(bool new_faced_forward)
{
    faced_forward = new_faced_forward;
}

void Mob::SetY(float new_y)
{
    position.y = new_y;
    sprite.setPosition(position);
}
