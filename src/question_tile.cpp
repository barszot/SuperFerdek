#include "question_tile.h"
#include <iostream>
QuestionTile::QuestionTile()
{
    setup(12, sf::Vector2f(0.f, 0.f));
    activated = false;
    texture_setup();
}
QuestionTile::QuestionTile(const int& type, const sf::Vector2f& position)
{
    setup(type, position);
    activated = false;
    texture_setup();
}
QuestionTile::~QuestionTile()
{

}
void QuestionTile::activate_tile()
{
    if (activated==false)
    {
        activated = true;
        sprite.setTexture(second_texture);
        action();
    }
    else
    {
        this->mob_ptr = nullptr;
    }
}

void QuestionTile::texture_setup()
{
    this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(115, 31, 16, 16));
    sprite.setTexture(texture);
    this->second_texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(6*16, 16, 16, 16));

}
void QuestionTile::action()
{

}

bool QuestionTile::get_activated() const
{
    return activated;
}
