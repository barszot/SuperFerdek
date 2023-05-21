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
    this->mob_ptr = nullptr;

    this->type = type;
    switch(type)
    {
        case 0:
            this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(32, 0, 16, 16));
            sprite.setTexture(texture);
            break;

        default:
            this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(48, 0, 16, 16));
            sprite.setTexture(texture);
            break;

    }
    this->position = position;
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

void Tile::Activated()
{
    
}

std::shared_ptr<Mob> Tile::GetMobPtr() const
{
    return mob_ptr;
}
