#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "tile_manager.h"
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
        void DrawTile(const Tile& tile);
        void DrawTileCollection(const TileManager& tile_manager);
        void UpdateView(const float& player_x, const float& min_x, const float& max_x);
        sf::Vector2u GetActualSize();

};

#endif