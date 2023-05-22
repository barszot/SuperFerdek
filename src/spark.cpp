#include "spark.h"

Spark::Spark()
{
    Setup();
}
Spark::Spark(sf::Vector2f position)
{
    this->position = position;
    Setup();
}
Spark::~Spark()
{

}
void Spark::Update(float delta_time)
{
    lifespan -= delta_time;
    if(lifespan <= 0.f)
    {
        marked_for_death = true;
        feedback = true;
    }
}

void Spark::Setup(){
    this->lifespan = 0.2f;
    this->type = 2;
    this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(136, 47, 16, 16));
    sprite.setTexture(this->texture);
    sprite.setPosition(this->position);
    sprite.setOrigin(0, 32);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));
}