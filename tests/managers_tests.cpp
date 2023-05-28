#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/tile_manager.h"
#include "../src/mob_manager.h"

TEST_CASE("TileManager tests", "[tile_manager]") 
{

    TileManager tile_manager;
    SECTION("testing default initialization")
    {
        CHECK(tile_manager.get_level() == 1);
    }
    SECTION("testing setup function")
    {
        tile_manager.setup(2);
        CHECK(tile_manager.get_level() == 2);
        tile_manager.setup(1);
        CHECK(tile_manager.get_level() == 1);
    }
    SECTION("testing loading next level")
    {
        tile_manager.load_next_level();
        CHECK(tile_manager.get_level() == 2);
        tile_manager.load_next_level();
        CHECK(tile_manager.get_level() == 3);    
    }
    SECTION("testing size")
    {
        int x1 = tile_manager.get_tiles().size();
        int y1 = tile_manager.get_tiles()[0].size();
        int x2 = tile_manager.get_length();
        int y2 = tile_manager.get_height();
        CHECK(x1 == x2);
        CHECK(y1 == y2);
    }
}
