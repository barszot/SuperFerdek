#include <SFML/Graphics.hpp>
#include "src/window.h"
#include "src/tile.h"
#include "src/mario.h"
#include "src/tile_manager.h"
#include <iostream>
int main()
{
    Window window("Super Ferdek", sf::Vector2u(1024, 512));
    TileManager tile_manager;
    Mario mario;
    while(!window.IsDone()){
        window.BeginDraw();
        window.DrawTileCollection(tile_manager);
        window.UpdateView(mario.GetPosition().x, 0, 16384);

        window.Draw(mario.GetSprite());
        mario.Update();

        window.Update();
        window.EndDraw();
    }
    window.Destroy();
    return 0;
}