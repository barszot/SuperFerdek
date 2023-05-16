#ifndef QUESTION_TILE_H
#define QUESTION_TILE_H
#include "tile.h"
class QuestionTile : public Tile
{
    protected:
        sf::Texture second_texture;
        void ChangeTexture();
        bool activated;
        virtual void Action();
        void TextureSetup();
    public:
        QuestionTile();
        QuestionTile(const int& type, const sf::Vector2f& position);
        virtual ~QuestionTile();
        virtual void Activated();
        bool GetActivated() const;

};

#endif