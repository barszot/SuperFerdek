#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/window.h"
#include "../src/game.h"


TEST_CASE("Game tests", "[game]") 
{
    Window window;
    Game game(window, 5);
    SECTION("testing default initialization")
    { 
        CHECK(game.get_is_done() == false);
        CHECK(game.get_is_window_done() == false);
        CHECK(game.get_is_won() == false);
        CHECK(game.get_coins_earned_earlier() == 0);
    }
}