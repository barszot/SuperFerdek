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
        int length;
        int height; //domyslnie 16
        int level;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;

    public:
        TileManager();
        TileManager(const int& level);
        ~TileManager();
        void setup(const int& level);

        const std::vector<std::vector<std::unique_ptr<Tile>>>& get_tiles() const;
        int get_length() const;
        int get_height() const;
        int get_level() const;
        bool check_tile(int x, int y) const;
        bool react_if_tile_is_coin(int x, int y, int& coins);
        std::shared_ptr<Mob> tile_activation(int x, int y);
        void load_next_level();
};

#endif