#ifndef FERDEK_H
#define FERDEK_H
#include "SFML/Graphics.hpp"
class Ferdek
{
private:
    sf::Texture texture_sheet;
    sf::Sprite sprite;
    sf::Vector2f position;
    float min_horizontal_speed;
    float max_horizontal_speed;
    float acceleration;
    float max_jump_time;
    float jump_speed;
    float is_small_jump_heigth;
    float is_big_jump_heigth;
    float left_speed;
    float right_speed;
    float gravity_speed;
    bool is_jumping;
    float remaining_jump_time;
    bool is_big;
    bool is_dead;
    bool is_running;
    bool frame;
    float max_time_before_change;
    float current_time_before_change;

    sf::IntRect ferdek_texture_list[2][2][4][2]; // faced_forward?, is_big?, akcja, klatka
public:
    Ferdek();
    ~Ferdek();
    bool is_crouching;
    bool faced_forward;
    void reset(bool reset_completely);
    void update(float delta_time);
    const sf::Sprite &get_sprite() const;
    const sf::Vector2f &get_position() const;
    bool left_collision;
    bool right_collision;
    bool top_collision;
    bool bottom_collision;
    void set_x(const float &new_x);
    void set_y(const float &new_y);
    void set_position(const sf::Vector2f& new_position);
    bool get_is_jumping() const;
    float get_jump_speed() const;
    float get_remaining_jump_time() const;
    void decrease_remaining_jump_time(float delta_time);
    void start_jumping();
    void stop_jumping_instantly();
    void instant_kill();
    bool get_is_big() const;
    void set_is_big(bool is_ferdek_big_now);
    bool get_is_dead() const;
    void set_sprite_origin(int x, int y);
};

#endif