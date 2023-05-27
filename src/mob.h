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
        bool IsFacedForward() const;
        float GetSpeed() const;
        void ToggleFacedForward();
        sf::Vector2f GetPosition() const;
        sf::Sprite GetSprite() const;
        void Move(float delta_time);
        virtual void Update(float delta_time);
        bool GetBottomCollision() const;
        void ToggleBottomCollision();
        void SetBottomCollision(bool new_bottom_collision);
        void SetFacedForward(bool new_faced_forward);
        void SetY(float new_y);
        void SetMarkedForDeath(bool is_marked);
        bool GetMarkedForDeath() const;
        virtual void MarkForDeathIfNecessary(sf::Vector2f ferdek_position, bool is_ferdek_big);
        bool GetFeedback() const;
        int GetType() const;
};  

#endif