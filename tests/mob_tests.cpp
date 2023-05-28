#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/mob.h"
#include "../src/beer.h"
#include "../src/spark.h"


TEST_CASE("Mob tests", "[mob]") 
{
    Mob mob;
    SECTION("testing default initialization")
    {
        CHECK(mob.get_is_faced_forward() == true);
        CHECK(mob.get_bottom_collision() == false);
        CHECK(mob.get_feedback() == false);
        CHECK(mob.get_marked_for_death() == false);

    }
    SECTION("check toggling faced_forward")
    {
        CHECK(mob.get_is_faced_forward() == true);
        mob.toggle_faced_forward();
        CHECK(mob.get_is_faced_forward() == false);
        mob.toggle_faced_forward();
        CHECK(mob.get_is_faced_forward() == true);
    }
    SECTION("check toggling bottom_collision")
    {
        CHECK(mob.get_bottom_collision() == false);
        mob.toggle_bottom_collision();
        CHECK(mob.get_bottom_collision() == true);
        mob.toggle_bottom_collision();
        CHECK(mob.get_bottom_collision() == false);
    }
    
    SECTION("testing setting Y")
    {
        mob.set_y(20.f);
        CHECK(mob.get_position().y == 20.f);
        mob.set_y(40.f);
        CHECK(mob.get_position().y == 40.f);
    }
    
}
TEST_CASE("Beer tests", "[beer]")
{
    Beer beer;
    SECTION("testing default initialization")
    {
        CHECK(beer.get_is_faced_forward() == true);
        CHECK(beer.get_bottom_collision() == false);
        CHECK(beer.get_feedback() == false);
        CHECK(beer.get_marked_for_death() == false);
        CHECK(beer.get_type() == 1);
    }
    SECTION("testing being taken by ferdek")
    {
        CHECK(beer.get_marked_for_death() == false);
        CHECK(beer.get_feedback() == false);
        sf::Vector2f ferdek_position(8.f, 8.f);
        beer.mark_for_death_if_necessary(ferdek_position, false);
        CHECK(beer.get_marked_for_death() == true);
        CHECK(beer.get_feedback() == true);
    }
}
TEST_CASE("Spark tests", "[spark]")
{
    Spark spark;
    SECTION("testing default initialization")
    {
        CHECK(spark.get_is_faced_forward() == true);
        CHECK(spark.get_bottom_collision() == false);
        CHECK(spark.get_feedback() == false);
        CHECK(spark.get_marked_for_death() == false);
        CHECK(spark.get_type() == 2);
    }
    SECTION("testing destroying")
    {
        CHECK(spark.get_feedback() == false);
        CHECK(spark.get_marked_for_death() == false);
        spark.update(0.1f);
        CHECK(spark.get_feedback() == false);
        CHECK(spark.get_marked_for_death() == false);
        spark.update(0.2f);
        CHECK(spark.get_feedback() == true);
        CHECK(spark.get_marked_for_death() == true);
    }
}

