#ifndef PAZDZIOCH_H
#define PAZDZIOCH_H
#include "enemy.h"
class Pazdzioch : public Enemy
{
    private:
        void setup();
        float max_three_frames_time;
        float current_three_frames_time;
        int current_frame;
        sf::IntRect pazdzioch_texture_list[4];
    public:
        Pazdzioch();
        Pazdzioch(sf::Vector2f position);
        ~Pazdzioch();
        virtual void mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big);
        virtual void update(float delta_time);

};


#endif