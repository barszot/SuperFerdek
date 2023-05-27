#ifndef MOB_MANAGER_H
#define MOB_MANAGER_H
#include "mob.h"
#include "beer.h"
#include "spark.h"
#include "enemy.h"
#include "pazdzioch.h"
#include <memory>
class MobManager
{
    private:
        int length; //dla pierwszego poziomu 512
        int height; //domyslnie 16
        int level;
        std::vector<std::shared_ptr<Mob>> mobs;
    public:
        MobManager();
        MobManager(const int& level);
        ~MobManager();
        void setup(const int& level);
        const std::vector<std::shared_ptr<Mob>>& get_mobs() const;
        int get_length() const;
        int get_height() const;
        int get_level() const;
        void load_next_level();
        void reset_mobs();
};
#endif