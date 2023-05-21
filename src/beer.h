#include "mob.h"
#include <cmath>
class Beer : public Mob
{
    private:
        void Setup();
    public:
        Beer();
        Beer(sf::Vector2f position);
        ~Beer();
        virtual void MarkForDeathIfNecessary(sf::Vector2f ferdek_position);

};