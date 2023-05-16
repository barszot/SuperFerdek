#include "tile_manager.h"
#include "question_tile.h"
#include <iostream>
TileManager::TileManager()
{
    Setup(512, 16, 1);
}
TileManager::TileManager(const int& length, const int& height, const int& level)
{
    Setup(length, height, level);
}
TileManager::~TileManager()
{

}
void TileManager::Setup(const int& length, const int& height, const int& level)
{
    this->length = length;
    this->height = height;
    this->level = level;
    sf::Image level_sheet;
    switch(level)
    {
        case 1:
            level_sheet.loadFromFile("src/imgs/tiles_level_1.png");
            break;
        default:
            return;
    }
    for(int i=0;i<length; i++)
    {
        std::vector<std::unique_ptr<Tile>> col;
        for(int j=0;j<height; j++)
        {
            int type = -1;

            sf::Color pixel_color = level_sheet.getPixel(i, j);
            if(sf::Color(255, 0, 0) == pixel_color)
            {
                type = 0;
            }
            else if(sf::Color(128, 0, 0) == pixel_color)
            {
                type = 1;
            }
            else if(sf::Color(255, 255, 0) == pixel_color)
            {
                type = 10;
            }


            if (type == -1)
            {
                col.push_back(nullptr);
            }
            else
            {
                sf::Vector2f tile_position(i*32, j*32);
                if(type<10){
                    col.push_back(std::make_unique<Tile>(type, tile_position));    
                }
                else if(type<20)
                {
                    col.push_back(std::make_unique<QuestionTile>(type, tile_position));    

                }
            }

        }

        tiles.push_back(std::move(col));
    }

}



int TileManager::GetLength() const
{
    return length;
}
int TileManager::GetHeigth() const
{
    return height;
}
int TileManager::GetLevel() const
{
    return level;
}

bool TileManager::CheckTile(int x, int y) const
{
    return nullptr!=tiles[x][y];
}

void TileManager::TileActivation(int x, int y, bool is_ferdek_big)
{
    if(CheckTile(x, y)){
        tiles[x][y]->Activated(is_ferdek_big);
    }
}

const std::vector<std::vector<std::unique_ptr<Tile>>>& TileManager::GetTiles() const
{
    return tiles;
}
