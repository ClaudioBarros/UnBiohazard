#pragma once    

#include "GameObject.h"
#include "Sprite.h"

struct TileSet
{
private:   
    GameObject& m_go;
    Sprite* m_tileSet;
    int m_rows;
    int m_columns;
    int m_rowSize;
    int m_columnSize;
    int m_tileWidth;
    int m_tileHeight;

public:
    TileSet(int tileWidth, 
            int tileHeight,
            std::string file,
            GameObject& associated);
    
    void RenderTile(unsigned index, float x, float y);

    int GetTileWidth();

    int GetTileHeight();

};
