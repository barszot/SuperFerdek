#include "question_tile_beer.h"

QuestionTileBeer::QuestionTileBeer()
{
    setup(4, sf::Vector2f(50.f, 50.f));
    activated = false;
    texture_setup();
}

QuestionTileBeer::QuestionTileBeer(const int& type, const sf::Vector2f& position)
{
    setup(type, position);
    activated = false;
    texture_setup();
}
QuestionTileBeer::~QuestionTileBeer()
{

}
void QuestionTileBeer::action()
{
    sf::Vector2f beer_position = position;
    beer_position.y += 32.f;
    this->mob_ptr = std::make_shared<Beer>(beer_position);
    //mobs.push_back(std::make_shared<Beer>(beer_position));
}
