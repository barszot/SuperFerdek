#ifndef SPARK_H
#define SPARK_H
#include "mob.h"
class Spark : public Mob
{
    private:
        float lifespan;
        void Setup();
    public:
        Spark();
        Spark(sf::Vector2f position);
        ~Spark();
        virtual void Update(float delta_time);

};

#endif