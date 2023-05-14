#include <SFML/Graphics.hpp>
#include "src/window.h"
#include "src/tile.h"
#include "src/tile_manager.h"
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    TileManager tile_manager;
    while(!window.IsDone()){
        window.BeginDraw();
        window.DrawTileCollection(tile_manager);
        window.Update();
        window.EndDraw();
    }
    window.Destroy();
    return 0;
}