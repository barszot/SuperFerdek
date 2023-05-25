#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ferdek.h"

static const double eps = 0.00000001;

bool compare(double a, double b){
    if (a-eps<b && a+eps>b)
        {
            return true;
        }
    return false;
}

TEST_CASE("Ferdek tests", "[ferdek]") 
{

    Ferdek ferdek;

    SECTION("testing start initialization")
    {
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_is_big() == false);
        CHECK(ferdek.get_position() == sf::Vector2f(160.f, 352.f));
    }
    SECTION("set movement and collision booleans after initialization")
    {
        CHECK(ferdek.is_crouching == false);
        CHECK(ferdek.get_is_jumping() == false);
        CHECK(ferdek.faced_forward == true);
        CHECK(ferdek.bottom_collision == false);
        CHECK(ferdek.top_collision == false);
        CHECK(ferdek.left_collision == false);
        CHECK(ferdek.right_collision == false);
    }
    SECTION("check instant killing")
    {
        CHECK(ferdek.get_is_dead() == false);
        ferdek.instant_kill();
        CHECK(ferdek.get_is_dead() == true);
    }
    SECTION("set is big and test non-complete and complete reset")
    {
        CHECK(ferdek.get_is_big() == false);
        ferdek.set_is_big(true);
        CHECK(ferdek.get_is_big() == true);
        ferdek.reset(false);
        CHECK(ferdek.get_is_big() == true);
        ferdek.reset(true);
        CHECK(ferdek.get_is_big() == false);        
    }
}
