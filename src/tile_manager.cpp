#include "tile_manager.h"

#include <iostream>
TileManager::TileManager()
{
    Setup(1);
}
TileManager::TileManager(const int& level)
{
    Setup(level);
}
TileManager::~TileManager()
{

}

void TileManager::Setup(const int& level)
{
    this->tiles.clear();
    this->level = level;
    sf::Image level_sheet;
    std::string path = "src/imgs/sheet_level_" + std::to_string(level) + ".png";
    level_sheet.loadFromFile(path);

    this->height = level_sheet.getSize().y;
    this->length = level_sheet.getSize().x;
    //std::cout<<level<<" "<<height<<" "<<length<<"\n";
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
            else if(sf::Color(255, 128, 0) == pixel_color)
            {
                type = 11;
            }
            else if(sf::Color(100, 100, 100) == pixel_color)
            {
                type = 100;
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
                else if(type==10)
                {
                    col.push_back(std::make_unique<QuestionTileBeer>(type, tile_position));    

                }
                else if(type==11)
                {
                    col.push_back(std::make_unique<QuestionTileCoin>(type, tile_position));    

                }
                else if(type == 100)
                {
                   col.push_back(std::make_unique<Coin>(type, tile_position));    
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

std::shared_ptr<Mob> TileManager::TileActivation(int x, int y)
{
    if(CheckTile(x, y)){
        tiles[x][y]->activate_tile();
        return tiles[x][y]->get_mob_ptr();
    }
    return nullptr;
}

const std::vector<std::vector<std::unique_ptr<Tile>>>& TileManager::GetTiles() const
{
    return tiles;
}

bool TileManager::ReactIfTileIsCoin(int x, int y, unsigned int& coins)
{
    if(CheckTile(x, y))
    {
        if(tiles[x][y]->get_is_coin()){
            tiles[x][y].reset();
            coins++;
            return true;
        }
    }
    return false;
}
void TileManager::load_next_level()
{
    this->level+=1;
    //std::cout<<"nowy poziom " << level;

    Setup(level);
}