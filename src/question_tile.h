#ifndef QUESTION_TILE_H
#define QUESTION_TILE_H
#include "tile.h"
class QuestionTile : public Tile
{
    protected:
        sf::Texture second_texture;
        bool activated;
        virtual void action();
        void texture_setup();
    public:
        QuestionTile();
        QuestionTile(const int& type, const sf::Vector2f& position);
        virtual ~QuestionTile();
        virtual void activate_tile();
        bool get_activated() const;

};

#endif