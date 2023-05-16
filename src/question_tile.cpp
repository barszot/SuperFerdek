#include "question_tile.h"
#include <iostream>
QuestionTile::QuestionTile()
{
    Setup(4, sf::Vector2f(50.f, 50.f));
    activated = false;
    TextureSetup();

}
QuestionTile::QuestionTile(const int& type, const sf::Vector2f& position)
{
    Setup(type, position);
    activated = false;
    TextureSetup();
}
QuestionTile::~QuestionTile()
{

}
void QuestionTile::Activated(bool is_ferdek_big)
{
    if (activated==false)
    {
        activated = true;
        sprite.setTexture(second_texture);
        Action();
    }
}

void QuestionTile::TextureSetup()
{
    this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(48, 16, 16, 16));
    sprite.setTexture(texture);
    this->second_texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(6*16, 16, 16, 16));

}
void QuestionTile::Action()
{

}

