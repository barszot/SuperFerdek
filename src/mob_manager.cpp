#include "mob_manager.h"
#include <iostream>
MobManager::MobManager()
{
    setup(1);
}
MobManager::MobManager(const int& level)
{
    setup(level);
}
MobManager::~MobManager()
{
    
}
void MobManager::setup(const int& level)
{
    this->mobs.clear();
    this->level = level;
    sf::Image level_sheet;
    std::string path = "src/imgs/mobs_level_" + std::to_string(level) + ".png";
    level_sheet.loadFromFile(path);
    this->height = level_sheet.getSize().y;
    this->length = level_sheet.getSize().x;
    //std::cout<<level<<" "<<height<<" "<<length<<"\n";
    for(int i=0;i<length; i++)
    {
        for(int j=0;j<height; j++)
        {
            int type = 0;

            sf::Color pixel_color = level_sheet.getPixel(i, j);
            if(sf::Color(0, 0, 0) == pixel_color)
            {
                type = -1;
            }
            else if(sf::Color(255, 0, 0) == pixel_color)
            {
                type = -2;
            }
            sf::Vector2f mob_position(i*32, j*32);
            if(type==-1){
                mobs.push_back(std::make_shared<Pazdzioch>(mob_position));
            }
        }
    }
    //std::cout<<level<<" "<<mobs.size()<<"\n";
}
const std::vector<std::shared_ptr<Mob>>& MobManager::get_mobs() const
{
    return mobs;
}
int MobManager::get_length() const
{
    return length;
}
int MobManager::get_height() const
{
    return height;
}
int MobManager::get_level() const
{
    return level;
}
void MobManager::load_next_level()
{
    this->level+=1;
    setup(level);
}
