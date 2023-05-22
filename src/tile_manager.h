#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H
#include "tile.h"
#include "question_tile.h"
#include <memory>
#include <typeinfo>

class TileManager
{
    private:
        int length; //dla pierwszego poziomu 512
        int height; //domyslnie 16
        int level;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        void Setup(const int& length, const int& height, const int& level);
    public:
        TileManager();
        TileManager(const int& length, const int& height, const int& level);
        ~TileManager();
        const std::vector<std::vector<std::unique_ptr<Tile>>>& GetTiles() const;
        int GetLength() const;
        int GetHeigth() const;
        int GetLevel() const;
        bool CheckTile(int x, int y) const;
        bool ReactIfTileIsCoin(int x, int y, unsigned int& coins);
        std::shared_ptr<Mob> TileActivation(int x, int y);

};

#endif