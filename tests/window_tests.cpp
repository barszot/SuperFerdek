#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/window.h"


TEST_CASE("Window tests", "[window]") 
{
    SECTION("testing default initialization")
    {
        Window window;
        CHECK(window.get_window_title() == "Window");
        CHECK(window.get_window_size() == sf::Vector2u(512, 512));
        CHECK(window.get_is_done() == false);
        CHECK(window.get_is_fullscreen() == false);
        CHECK(window.get_actual_size() == window.get_window_size());
    }
    SECTION("testing custom initialization")
    {
        Window my_window("SuperGame", sf::Vector2u(400, 600));
        CHECK(my_window.get_window_title() == "SuperGame");
        CHECK(my_window.get_window_size() == sf::Vector2u(400, 600));
        CHECK(my_window.get_is_done() == false);
        CHECK(my_window.get_is_fullscreen() == false);
        CHECK(my_window.get_actual_size() == my_window.get_window_size());
    }
    SECTION("testing toggling fullscreen")
    {
        Window toggle_window("ToggleWindow", sf::Vector2u(200, 200));
        CHECK(toggle_window.get_window_title() == "ToggleWindow");
        CHECK(toggle_window.get_window_size() == sf::Vector2u(200, 200));
        CHECK(toggle_window.get_is_done() == false);
        CHECK(toggle_window.get_is_fullscreen() == false);
        CHECK(toggle_window.get_actual_size() == toggle_window.get_window_size());
        toggle_window.toggle_fullscreen();
        CHECK(toggle_window.get_is_fullscreen() == true);
        CHECK(toggle_window.get_window_title() == "ToggleWindow");
        CHECK(toggle_window.get_window_size() == sf::Vector2u(200, 200));
        CHECK(toggle_window.get_is_done() == false);
        CHECK(toggle_window.get_actual_size().x>toggle_window.get_window_size().x);
        CHECK(toggle_window.get_actual_size().y>toggle_window.get_window_size().y);
        toggle_window.toggle_fullscreen();
        CHECK(toggle_window.get_window_title() == "ToggleWindow");
        CHECK(toggle_window.get_window_size() == sf::Vector2u(200, 200));
        CHECK(toggle_window.get_is_done() == false);
        CHECK(toggle_window.get_is_fullscreen() == false);
        CHECK(toggle_window.get_actual_size() == toggle_window.get_window_size());

    }
}