#include "question_tile_coin.h"

QuestionTileCoin::QuestionTileCoin()
{
    setup(4, sf::Vector2f(50.f, 50.f));
    activated = false;
    texture_setup();
}

QuestionTileCoin::QuestionTileCoin(const int& type, const sf::Vector2f& position)
{
    setup(type, position);
    activated = false;
    texture_setup();
}
QuestionTileCoin::~QuestionTileCoin()
{

}
void QuestionTileCoin::action()
{
    sf::Vector2f coin_position = position;
    coin_position.y += 32.f;
    this->mob_ptr = std::make_shared<Spark>(coin_position);
    //mobs.push_back(std::make_shared<Beer>(beer_position));
}
