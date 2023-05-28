#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/ferdek.h"

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
        ferdek.reset(true);
        ferdek.set_is_big(true);
        CHECK(ferdek.get_is_big() == true);
        ferdek.instant_kill();
        CHECK(ferdek.get_is_dead() == true);
        ferdek.reset(true);
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
    SECTION("check not_instant_killing")
    {
        ferdek.set_is_big(true);
        CHECK(ferdek.get_is_big() == true);
        CHECK(ferdek.get_is_dead() == false);
        ferdek.not_instant_kill();
        CHECK(ferdek.get_is_big() == false);
        CHECK(ferdek.get_is_dead() == false);
        ferdek.not_instant_kill();
        CHECK(ferdek.get_is_big() == false);
        CHECK(ferdek.get_is_dead() == true);
    }
    SECTION("setting position")
    {
        ferdek.reset(true);
        CHECK(ferdek.get_is_dead() == false);
        CHECK(ferdek.get_position() == sf::Vector2f(160.f, 352.f));
        ferdek.set_position(sf::Vector2f(40.f, 75.f));
        CHECK(ferdek.get_position() == sf::Vector2f(40.f, 75.f));
        ferdek.set_x(60.f);
        CHECK(ferdek.get_position() == sf::Vector2f(60.f, 75.f));
        ferdek.set_y(120.f);
        CHECK(ferdek.get_position() == sf::Vector2f(60.f, 120.f));
    }
    SECTION("jumping")
    {
        ferdek.reset(true);
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_remaining_jump_time()==0.f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.set_is_big(true);
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_remaining_jump_time()==0.f);
        CHECK(ferdek.get_jump_speed()==600.f);
        ferdek.set_is_big(false);
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_remaining_jump_time()==0.f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.start_jumping();
        CHECK(ferdek.get_is_jumping()==true);
        CHECK(ferdek.get_remaining_jump_time()==0.15f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.decrease_remaining_jump_time(0.04f);
        CHECK(ferdek.get_is_jumping()==true);
        CHECK(abs(ferdek.get_remaining_jump_time()-0.11f)<0.00001f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.decrease_remaining_jump_time(0.12f);
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_remaining_jump_time()==0.f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.start_jumping();
        CHECK(ferdek.get_is_jumping()==true);
        CHECK(ferdek.get_remaining_jump_time()==0.15f);
        CHECK(ferdek.get_jump_speed()==400.f);
        ferdek.stop_jumping_instantly();
        CHECK(ferdek.get_is_jumping()==false);
        CHECK(ferdek.get_remaining_jump_time()==0.f);
        CHECK(ferdek.get_jump_speed()==400.f);
    }
}
