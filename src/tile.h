#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
    protected:
        sf::Texture texture;
        sf::Vector2f position;
        sf::Sprite sprite;
        int type;
        void Setup(const int& type, const sf::Vector2f& position);
    public:
        Tile();
        Tile(const int& type, const sf::Vector2f& position);
        virtual ~Tile();
        sf::Vector2f GetPositon() const;
        const sf::Sprite& GetSprite() const;
        int GetType() const;
};


#endif