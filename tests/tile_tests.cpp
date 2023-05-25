#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/tile.h"
#include "../src/coin.h"
#include "../src/question_tile.h"
#include "../src/question_tile_beer.h"
#include "../src/question_tile_coin.h"

TEST_CASE("Tile tests", "[tile]") 
{
    SECTION("testing default initialization")
    {
        Tile tile_default;
        CHECK(tile_default.get_type() == 0);
        CHECK(tile_default.get_position() == sf::Vector2f(0.f, 0.f));
        CHECK(tile_default.get_mob_ptr() == nullptr);
        CHECK(tile_default.get_is_coin() == false);

    }
    SECTION("testing tile with chosen type and position")
    {
        Tile tile_with_params(4, sf::Vector2f(16.f, 32.f));
        CHECK(tile_with_params.get_type() == 4);
        CHECK(tile_with_params.get_position() == sf::Vector2f(16.f, 32.f));
        CHECK(tile_with_params.get_mob_ptr() == nullptr);
        CHECK(tile_with_params.get_is_coin() == false);
    }
}


TEST_CASE("Coin tests", "[coin]")
{
    SECTION("basic tests")
    {
        Coin coin;
        CHECK(coin.get_type() == 100);
        CHECK(coin.get_position() == sf::Vector2f(0.f, 0.f));
        CHECK(coin.get_mob_ptr() == nullptr);
        CHECK(coin.get_is_coin() == true);        
    }
}

TEST_CASE("Question tiles tests", "[question_tile]")
{
    SECTION("basic tests")
    {
        QuestionTile question_tile;
        CHECK(question_tile.get_type() == 12);
        CHECK(question_tile.get_position() == sf::Vector2f(0.f, 0.f));
        CHECK(question_tile.get_is_coin() == false);
        CHECK(question_tile.get_mob_ptr() == nullptr);
        CHECK(question_tile.get_activated() == false);

        question_tile.activate_tile();
        CHECK(question_tile.get_activated() == true);
    }

}
TEST_CASE("Question tile with beer tests", "[question_tile_beer]")
{
    SECTION("testing default initialization")
    {   
        QuestionTileBeer question_tile_beer;
        CHECK(question_tile_beer.get_type() == 10);
        CHECK(question_tile_beer.get_position() == sf::Vector2f(0.f, 0.f));
        CHECK(question_tile_beer.get_is_coin() == false);
        CHECK(question_tile_beer.get_mob_ptr() == nullptr);
        CHECK(question_tile_beer.get_activated() == false);
    }
    SECTION("testing action")
    {
        QuestionTileBeer question_tile_beer;
        CHECK(question_tile_beer.get_activated() == false);
        CHECK(question_tile_beer.get_mob_ptr() == nullptr);
        question_tile_beer.activate_tile();
        CHECK(question_tile_beer.get_activated() == true);
        CHECK(question_tile_beer.get_mob_ptr() != nullptr);
        CHECK(question_tile_beer.get_mob_ptr()->GetType()==1);
        CHECK(question_tile_beer.get_position().x == question_tile_beer.get_mob_ptr()->GetPosition().x);
        CHECK(question_tile_beer.get_position().y+32.f == question_tile_beer.get_mob_ptr()->GetPosition().y);
        question_tile_beer.activate_tile();
        CHECK(question_tile_beer.get_activated() == true);
        CHECK(question_tile_beer.get_mob_ptr() == nullptr);
    }
}
TEST_CASE("Question tile with coin tests", "[question_tile_coin]")
{
    SECTION("testing default initialization")
    {   
        QuestionTileCoin question_tile_coin;
        CHECK(question_tile_coin.get_type() == 11);
        CHECK(question_tile_coin.get_position() == sf::Vector2f(0.f, 0.f));
        CHECK(question_tile_coin.get_is_coin() == false);
        CHECK(question_tile_coin.get_mob_ptr() == nullptr);
        CHECK(question_tile_coin.get_activated() == false);
    }
    SECTION("testing action")
    {
        QuestionTileCoin question_tile_coin;
        CHECK(question_tile_coin.get_activated() == false);
        CHECK(question_tile_coin.get_mob_ptr() == nullptr);
        question_tile_coin.activate_tile();
        CHECK(question_tile_coin.get_activated() == true);
        CHECK(question_tile_coin.get_mob_ptr() != nullptr);
        CHECK(question_tile_coin.get_mob_ptr()->GetType()==2);
        CHECK(question_tile_coin.get_position().x == question_tile_coin.get_mob_ptr()->GetPosition().x);
        CHECK(question_tile_coin.get_position().y+32.f == question_tile_coin.get_mob_ptr()->GetPosition().y);
        question_tile_coin.activate_tile();
        CHECK(question_tile_coin.get_activated() == true);
        CHECK(question_tile_coin.get_mob_ptr() == nullptr);
    }
}