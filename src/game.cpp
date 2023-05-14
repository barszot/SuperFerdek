#include "game.h"

Game::Game() : window(Window("Super Ferdek", sf::Vector2u(1024, 512))), is_done(false) {}

Game::~Game() {}

void Game::GameSetup()
{

}

void Game::GameUpdate()
{
        if(window.IsDone()){
            EndGame();
            return;
        }
        window.BeginDraw();
        window.DrawTileCollection(tile_manager);
        window.Draw(ferdek.GetSprite());
        window.UpdateView(ferdek.GetPosition().x, 0, 16384);
        window.Update();
        ferdek.Update();
        window.EndDraw();
}

bool Game::IsDone()
{
    return is_done;
}
void Game::EndGame()
{
    is_done = true;
    window.Destroy();
}
void Game::ManagePlayerCollisionsAndGravity() {}
