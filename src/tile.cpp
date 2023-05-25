#include "tile.h"
Tile::Tile()
{
    setup(0, sf::Vector2f(0.f, 0.f));
    this->is_coin = false;

}
Tile::Tile(const int& type, const sf::Vector2f& position)
{
    setup(type, position);
}
void Tile::setup(const int& type, const sf::Vector2f& position)
{
    this->mob_ptr = nullptr;
    this->is_coin = false;
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
sf::Vector2f Tile::get_position() const
{
    return position;
}
sf::Sprite& Tile::get_sprite()
{
    return sprite;
}

int Tile::get_type() const
{
    return type;
}

void Tile::activate_tile()
{
    
}

std::shared_ptr<Mob> Tile::get_mob_ptr() const
{
    return mob_ptr;
}

bool Tile::get_is_coin() const
{
    return is_coin;
}