#include "mob.h"

class Beer : public Mob
{
    private:
        void Setup();
    public:
        Beer();
        Beer(sf::Vector2f position);
        ~Beer();
};