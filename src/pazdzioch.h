#ifndef PAZDZIOCH_H
#define PAZDZIOCH_H
#include "enemy.h"
class Pazdzioch : public Enemy
{
    private:
        void setup();
    public:
        Pazdzioch();
        Pazdzioch(sf::Vector2f position);
        ~Pazdzioch();
        virtual void MarkForDeathIfNecessary(sf::Vector2f ferdek_position, bool is_ferdek_big);

};


#endif