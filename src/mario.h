#ifndef MARIO_H
#define MARIO_H
#include "SFML/Graphics.hpp"
class Mario
{
    private:
        sf::Texture texture_sheet;
        sf::Sprite sprite;
        sf::Vector2f position;
        const float min_horizontal_warp;
        const float max_horizontal_warp;
        const float acceleration_warp;
        float left_warp;
        float right_warp;
        bool faced_forward;
    public:
        Mario();
        ~Mario();
        void Update();
        const sf::Sprite& GetSprite() const;
        const sf::Vector2f& GetPosition() const;
};

#endif