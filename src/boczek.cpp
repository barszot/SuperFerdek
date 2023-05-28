#include "boczek.h"
Boczek::Boczek()
{

    this->position = sf::Vector2f(0.f, 0.f);
    setup();

}
Boczek::Boczek(sf::Vector2f position)
{
    this->position = position;
    setup();
}
Boczek::~Boczek()
{

}
void Boczek::setup()
{
    this->type = -2;
    this->texture.loadFromFile("src/imgs/enemies.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 48);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
    this->speed = 500.f;
    this->current_frame = 0;
    this->max_two_frames_time = 0.2f;
    this->current_two_frames_time = max_two_frames_time;
    this->boczek_texture_list[0][1] = sf::IntRect(32, 0, 16, 32);
    this->boczek_texture_list[1][1] = sf::IntRect(48, 0, 16, 32);
    this->boczek_texture_list[0][0] = sf::IntRect(0, 0, 16, 32);
    this->boczek_texture_list[1][0] = sf::IntRect(16, 0, 16, 32);

    this->sprite.setTextureRect(boczek_texture_list[current_frame][faced_forward]);

}
void Boczek::mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big)
{

    if(abs(ferdek_position.x - position.x)<=24.f && (abs(ferdek_position.y-position.y)<=36.f+32.f && abs(ferdek_position.y-position.y) > 28.f+32.f))
    {
        marked_for_death = true;
    }
    else if(position.y > 16.5f*32)
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
    else if(std::pow(ferdek_position.x-position.x, 2) + std::pow(ferdek_position.y-position.y+32.f, 2) < 32.f*32.f)
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
void Boczek::update(float delta_time)
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
    current_two_frames_time -= delta_time;
    if(current_two_frames_time<=max_two_frames_time/2.f)
    {
        current_frame = 1;
        if(current_two_frames_time<0.f)
        {
            current_two_frames_time = max_two_frames_time;
        }
    }
    else
    {
        current_frame = 0;
    }

    this->sprite.setTextureRect(boczek_texture_list[current_frame][faced_forward]);
    
}
