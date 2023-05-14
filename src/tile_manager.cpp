#include "tile_manager.h"

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
    tile_types.clear();
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
        std::vector<int> column;
        for(int j=0;j<height; j++)
        {
            sf::Color pixel_color = level_sheet.getPixel(i, j);
            if(sf::Color(255, 0, 0) == pixel_color)
            {
                column.push_back(0);
            }
            else if(sf::Color(128, 0, 0) == pixel_color)
            {
                column.push_back(1);
            }
            else
            {
                column.push_back(-1);
            }
        }
        tile_types.push_back(column);
    }
    CreateTileCollection();
}
void TileManager::CreateTileCollection()
{
    tile_collection.clear();
    for(int i=0;i<length; i++)
    {
        for(int j=0;j<height; j++)
        {
            int tile_type = tile_types[i][j];
            if(tile_type>=0){
                sf::Vector2f tile_position(i*32, j*32);
                tile_collection.push_back(std::make_shared<Tile>(tile_type, tile_position));
            }
        }
    }
}

const std::vector<std::shared_ptr<Tile>>& TileManager::GetTileCollection() const {
    return tile_collection;
}

const std::vector<std::vector<int>>& TileManager::GetTileTypes() const
{
    return tile_types;
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