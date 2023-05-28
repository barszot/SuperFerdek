#ifndef BEER_H
#define BEER_H
#include "mob.h"

class Beer : public Mob
{
    private:
        void setup();
    public:
        Beer();
        Beer(sf::Vector2f position);
        ~Beer();
        virtual void mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big);

};
#endif