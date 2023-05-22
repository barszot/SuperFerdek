#ifndef QUESTION_TILE_COIN_H
#define QUESTION_TILE_COIN_H
#include "question_tile.h"
#include "spark.h"
class QuestionTileCoin : public QuestionTile
{
    protected:
        virtual void Action();
    public:
        QuestionTileCoin();
        QuestionTileCoin(const int& type, const sf::Vector2f& position);
        ~QuestionTileCoin();
};
#endif