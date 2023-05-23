#ifndef FERDEK_H
#define FERDEK_H
#include "SFML/Graphics.hpp"
class Ferdek
{
    private:
        sf::Texture texture_sheet;
        sf::Sprite sprite;
        sf::Vector2f position;
        float min_horizontal_warp;
        float max_horizontal_warp;
        float acceleration_warp;
        int max_mini_jumps;
        float mini_jump_height;
        float is_small_jump_heigth;
        float is_big_jump_heigth;
        float left_warp;
        float right_warp;
        float gravity_warp;
        bool is_jumping;
        float mini_jumps;
        bool is_big;
        bool is_dead;
        bool is_running;
        bool is_crouching;
        bool frame;
        float max_time_before_change;
        float current_time_before_change;

        sf::IntRect ferdek_texture_list[2][2][4][2]; // faced_forward?, is_big?, akcja, klatka
    public:
        Ferdek();
        ~Ferdek();
        bool faced_forward;
        void Reset();
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
        void InstantKill();
        bool IsBig() const;
        void SetIsBig(bool is_ferdek_big_now);
        bool IsDead() const;

};

#endif