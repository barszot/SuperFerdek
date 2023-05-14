#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H
#include "tile.h"
#include <memory>
class TileManager
{
    private:
        int length; //dla pierwszego poziomu 512
        int height; //domyslnie 16
        int level;
        std::vector<std::vector<int>> tile_types;
        std::vector<std::shared_ptr<Tile>> tile_collection; 
        void Setup(const int& length, const int& height, const int& level);
        void CreateTileCollection();
    public:
        TileManager();
        TileManager(const int& length, const int& height, const int& level);
        ~TileManager();

        const std::vector<std::shared_ptr<Tile>>& GetTileCollection() const;

        int GetLength() const;
        int GetHeigth() const;
        int GetLevel() const;

};

#endif