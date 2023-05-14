#include "tile.h"

Tile::Tile()
{
    Setup(0, sf::Vector2f(0.f, 0.f));
}
Tile::Tile(const int& type, const sf::Vector2f& position)
{
    Setup(type, position);
}
void Tile::Setup(const int& type, const sf::Vector2f& position)
{
    this->type = type;
    switch(type)
    {
        case 0:
            this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(32, 0, 16, 16));
            break;
        case 1:
            this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(48, 0, 16, 16));
            break;
        default:
            return;
    }
    this->position = position;
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f (2.0f, 2.0f));

}

Tile::~Tile()
{

}
sf::Vector2f Tile::GetPositon() const
{
    return position;
}
const sf::Sprite& Tile::GetSprite() const
{
    return sprite;
}

int Tile::GetType() const
{
    return type;
}