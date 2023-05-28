#ifndef BOCZEK_H
#define BOCZEK_H
#include "enemy.h"
class Boczek : public Enemy
{
    private:
        void setup();
        float max_two_frames_time;
        float current_two_frames_time;
        int current_frame;
        sf::IntRect boczek_texture_list[2][2]; //frame time, faced forward
    public:
        Boczek();
        Boczek(sf::Vector2f position);
        ~Boczek();
        virtual void mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big);
        virtual void update(float delta_time);

};


#endif