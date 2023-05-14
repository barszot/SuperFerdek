#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
    private:
        sf::Texture texture;
        sf::Vector2f position;
        sf::Sprite sprite;
        int type;
        void Setup(const int& type, const sf::Vector2f& position);
    public:
        Tile();
        Tile(const int& type, const sf::Vector2f& position);
        ~Tile();
        sf::Vector2f GetPositon() const;
        const sf::Sprite& GetSprite() const;
        int GetType() const;
};


#endif