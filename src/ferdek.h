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
        const int max_mini_jumps;
        float mini_jump_height;
        float left_warp;
        float right_warp;
        float gravity_warp;
        bool is_jumping;
        float mini_jumps;


    public:
        Ferdek();
        ~Ferdek();
        bool faced_forward;
        void Update(float time_warp);
        const sf::Sprite& GetSprite() const;
        const sf::Vector2f& GetPosition() const;
        bool left_collision;
        bool right_collision;
        bool top_collision;
        bool bottom_collision;
        void SetY(const float& new_y);
        bool IsJumping() const;
        float GetMiniJump() const;
        int GetNumberOfMiniJumps() const;
        void DecrementMiniJumps(float time_warp);
        void StartJumping();
        void StopJumpingInstantly();
};

#endif