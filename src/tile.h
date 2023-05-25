#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "mob.h"
#include <memory>
class Tile
{
    protected:
        sf::Texture texture;
        sf::Vector2f position;
        sf::Sprite sprite;
        int type;
        void setup(const int& type, const sf::Vector2f& position);
        std::shared_ptr<Mob> mob_ptr;
        bool is_coin;
    public:
        Tile();
        Tile(const int& type, const sf::Vector2f& position);
        virtual ~Tile();
        sf::Vector2f get_position() const;
        sf::Sprite& get_sprite();
        int get_type() const;
        virtual void activate_tile();
        std::shared_ptr<Mob> get_mob_ptr() const;
        bool get_is_coin() const;

};


#endif