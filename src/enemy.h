#ifndef ENEMY_H
#define ENEMY_H
#include "mob.h"
class Enemy : public Mob
{
    protected:
        float current_time_of_not_killing_ferdek;
        float max_time_of_not_killing_ferdek;
        bool can_kill_ferdek;
        //feedback = killed ferdek
    public:
        Enemy();
        ~Enemy();
        virtual void update(float delta_time);
        bool get_can_kill_ferdek() const;
        virtual void check_if_kills_ferdek(sf::Vector2f ferdek_position);
};
#endif