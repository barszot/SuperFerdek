#ifndef FERDEK_H
#define FERDEK_H
#include "SFML/Graphics.hpp"
class Ferdek
{
    private:
        sf::Texture texture_sheet;
        sf::Sprite sprite;
        sf::Vector2f position;
        const float min_horizontal_warp;
        const float max_horizontal_warp;
        const float acceleration_warp;
        const float gravity_warp;
        float left_warp;
        float right_warp;
        bool faced_forward;

    public:
        Ferdek();
        ~Ferdek();
        void Update();
        const sf::Sprite& GetSprite() const;
        const sf::Vector2f& GetPosition() const;
        bool left_collision;
        bool right_collision;
        bool top_collision;
        bool bottom_collision;
};

#endif