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
    this->texture.loadFromFile("src/imgs/enemies.png");
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
    this->speed = 100.f;
    this->current_frame = 0;
    this->max_three_frames_time = 1.f;
    this->current_three_frames_time = max_three_frames_time;
    this->pazdzioch_texture_list[0] = sf::IntRect(0, 32, 16, 16);
    this->pazdzioch_texture_list[1] = sf::IntRect(16, 32, 16, 16);
    this->pazdzioch_texture_list[2] = sf::IntRect(32, 32, 16, 16);
    this->pazdzioch_texture_list[3] = sf::IntRect(16, 32, 16, 16);

    this->sprite.setTextureRect(pazdzioch_texture_list[current_frame]);

}
void Pazdzioch::mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big)
{

    if(abs(ferdek_position.x - position.x)<=24.f && (abs(ferdek_position.y-position.y)<=36.f && abs(ferdek_position.y-position.y) > 28.f))
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
}
void Pazdzioch::update(float delta_time)
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
    int new_frame = current_frame;
    current_three_frames_time -= delta_time;
    if(current_three_frames_time<=max_three_frames_time/4.f)
    {
        new_frame = 3;
        if(current_three_frames_time<0.f)
        {
            current_three_frames_time = max_three_frames_time;
        }
    }
    else if(current_three_frames_time>max_three_frames_time/4.f && current_three_frames_time<=max_three_frames_time/2.f)
    {
        new_frame = 2;
    }
    else if(current_three_frames_time>max_three_frames_time/2.f && current_three_frames_time<=3*max_three_frames_time/4.f)
    {
        new_frame = 1;
    }
    else
    {
        new_frame = 0;
    }

    if(current_frame!=new_frame)
    {
        current_frame = new_frame;
        this->sprite.setTextureRect(pazdzioch_texture_list[current_frame]);
    }
}
