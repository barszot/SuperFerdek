#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H
#include "tile.h"
#include <memory>
#include <typeinfo>
#include "question_tile.h"
#include "question_tile_coin.h"
#include "question_tile_beer.h"
#include "coin.h"
class TileManager
{
    private:
        int length; //dla pierwszego poziomu 512
        int height; //domyslnie 16
        int level;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    public:
        TileManager();
        TileManager(const int& level);
        ~TileManager();
        void Setup(const int& level);
        const std::vector<std::vector<std::unique_ptr<Tile>>>& GetTiles() const;
        int GetLength() const;
        int GetHeigth() const;
        int GetLevel() const;
        bool CheckTile(int x, int y) const;
        bool ReactIfTileIsCoin(int x, int y, unsigned int& coins);
        std::shared_ptr<Mob> TileActivation(int x, int y);
        void load_next_level();
};

#endif