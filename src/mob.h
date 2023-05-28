#ifndef MOB_H
#define MOB_H
#include "SFML/Graphics.hpp"
#include <cmath>
class Mob
{
    protected:
        bool faced_forward;
        float speed;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        float gravity_speed;
        bool bottom_collision;
        bool marked_for_death;
        bool feedback;
        int type;
    public:
        Mob();
        virtual ~Mob();
        bool get_is_faced_forward() const;
        float get_speed() const;
        void toggle_faced_forward();
        sf::Vector2f get_position() const;
        sf::Sprite get_sprite() const;
        void move(float delta_time);
        virtual void update(float delta_time);
        bool get_bottom_collision() const;
        void toggle_bottom_collision();
        void set_bottom_collision(bool new_bottom_collision);
        void set_faced_forward(bool new_faced_forward);
        void set_y(float new_y);
        void set_marked_for_death(bool is_marked);
        bool get_marked_for_death() const;
        virtual void mark_for_death_if_necessary(sf::Vector2f ferdek_position, bool is_ferdek_big);
        bool get_feedback() const;
        int get_type() const;
};  

#endif