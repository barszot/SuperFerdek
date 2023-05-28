#ifndef SPARK_H
#define SPARK_H
#include "mob.h"
class Spark : public Mob
{
    private:
        float lifespan;
        void setup();
    public:
        Spark();
        Spark(sf::Vector2f position);
        ~Spark();
        virtual void update(float delta_time);

};

#endif