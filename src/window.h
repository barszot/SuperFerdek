#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "tile_manager.h"
#include "mob.h"
#include "ferdek.h"
class Window
{
    private:
        void setup(const std::string& title,
        const sf::Vector2u& size);
        void create();
        sf::RenderWindow render_window;
        sf::Vector2u window_size;
        std::string window_title;
        bool is_fullscreen;
        bool is_done;
        sf::Font comic_sans;
        bool in_lobby;



    public:
        Window();
        Window(const std::string& title,const sf::Vector2u& size);
        ~Window();
        std::string get_window_title() const;
        sf::Vector2u get_window_size() const;

        void begin_draw(sf::Color color = sf::Color::White);
        void end_draw();
        void update();
        bool get_is_done() const;
        bool get_is_fullscreen() const;
        void destroy();
        void toggle_fullscreen();
        void draw(const sf::Drawable& drawable);
        void draw_tile_collection(const TileManager& tile_manager, int current_ferdek_column);
        void draw_mobs(const std::vector<std::shared_ptr<Mob>>& mobs, float ferdek_position_x);
        void update_view(const float& player_x, const float& min_x, const float& max_x);
        sf::Vector2u get_actual_size() const;
        void draw_stats(const unsigned int& coins, const int& lives, const int& level, const float& player_x, const float& min_x, const float& max_x);
        bool start_window();
        void draw_ferdek(Ferdek& ferdek);
        void end_window_after_lost();
        void end_window_after_win(int result, int highscore);

};

#endif