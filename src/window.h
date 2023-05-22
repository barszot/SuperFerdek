#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "tile_manager.h"
#include "mob.h"
class Window
{
    private:
        void Setup(const std::string& title,
        const sf::Vector2u& size);
        void Create();
        sf::RenderWindow render_window;
        sf::Vector2u window_size;
        std::string window_title;
        bool is_fullscreen;
        bool is_done;
        sf::Font comic_sans;
    public:
        Window();
        Window(const std::string& title,const sf::Vector2u& size);
        ~Window();
        void BeginDraw();
        void EndDraw();
        void Update();
        bool IsDone() const;
        bool IsFullscreen() const;
        void Destroy();
        sf::Vector2u GetWindowSize() const;
        void ToggleFullscreen();
        void Draw(const sf::Drawable& drawable);
        void DrawTileCollection(const TileManager& tile_manager, int current_ferdek_column);
        void DrawMobs(const std::vector<std::shared_ptr<Mob>>& mobs, float ferdek_position_x);
        void UpdateView(const float& player_x, const float& min_x, const float& max_x);
        sf::Vector2u GetActualSize();
        void DrawStats(const unsigned int& coins, const int& lives, const float& player_x, const float& min_x, const float& max_x);
};

#endif