#include "coin.h"

Coin::Coin()
{
    setup(100, sf::Vector2f(0.f, 0.f));
    texture_setup();
    this->is_coin = true;
}
Coin::Coin(const int& type, const sf::Vector2f& position)
{
    setup(type, position);
    texture_setup();
    this->is_coin = true;
}
Coin::~Coin()
{

}
void Coin::texture_setup()
{
    this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(115, 48, 16, 16));
    sprite.setTexture(texture);
}