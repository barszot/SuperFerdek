#include "question_tile_beer.h"

QuestionTileBeer::QuestionTileBeer()
{
    Setup(4, sf::Vector2f(50.f, 50.f));
    activated = false;
    TextureSetup();
}

QuestionTileBeer::QuestionTileBeer(const int& type, const sf::Vector2f& position)
{
    Setup(type, position);
    activated = false;
    TextureSetup();
}
QuestionTileBeer::~QuestionTileBeer()
{

}
void QuestionTileBeer::Action()
{
    sf::Vector2f beer_position = position;
    beer_position.y += 32.f;
    this->mob_ptr = std::make_shared<Beer>(beer_position);
    //mobs.push_back(std::make_shared<Beer>(beer_position));
}
