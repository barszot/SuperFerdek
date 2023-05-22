#ifndef COIN_H
#define COIN_H
#include "tile.h"
class Coin : public Tile
{
    private:
        void TextureSetup();
    public:
        Coin();
        Coin(const int& type, const sf::Vector2f& position);
        ~Coin();
};
#endif