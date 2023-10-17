#include "TileSet.h"
#include "Sprite.h"
#include <cstring>

TileSet::TileSet(int tileWidth, 
                 int tileHeight,
                 std::string file,
                 GameObject& associated) : m_go(associated) 
{
    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;
    
    m_tileSet = new Sprite(associated, file);
    if(!m_tileSet)
    {
        printf("Failed texture loading at path %s: %s\n", file.c_str(), IMG_GetError());
        return;
    }

    m_columns = m_tileSet->GetWidth()/tileWidth;
    m_rows = m_tileSet->GetHeight()/tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    unsigned indexX = index % m_columns;
    unsigned indexY = index / m_columns;
     
    unsigned clipX = (unsigned)(indexX * m_tileWidth);
    unsigned clipY = (unsigned)(indexY * m_tileHeight);
    m_tileSet->SetClip(clipX, clipY, m_tileWidth, m_tileHeight);
    m_tileSet->Render(x, y);
}

int TileSet::GetTileWidth()
{
    return m_tileHeight;
}

int TileSet::GetTileHeight()
{
    return m_tileWidth;
}


