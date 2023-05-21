#ifndef QUESTION_TILE_BEER_H
#define QUESTION_TILE_BEER_H
#include "question_tile.h"
#include "beer.h"
#include <memory>
class QuestionTileBeer : public QuestionTile
{
    protected:
        virtual void Action();
    public:
        QuestionTileBeer();
        QuestionTileBeer(const int& type, const sf::Vector2f& position);
        ~QuestionTileBeer();
};

#endif