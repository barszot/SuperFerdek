#include "coin.h"

Coin::Coin()
{
    Setup(100, sf::Vector2f(50.f, 50.f));
    TextureSetup();
    this->is_coin = true;
}
Coin::Coin(const int& type, const sf::Vector2f& position)
{
    Setup(type, position);
    TextureSetup();
    this->is_coin = true;
}
Coin::~Coin()
{

}
void Coin::TextureSetup()
{
    this->texture.loadFromFile("src/imgs/map_textures.png", sf::IntRect(136, 28, 16, 16));
    sprite.setTexture(texture);
}