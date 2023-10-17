#include "TileMap.h"
#include "TileSet.h"
#include <fstream>
#include <string>
#include <cstring> 
#include "Helper.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, 
                 std::string file,
                 TileSet* tileSet) : Component(associated)
{
    Load(file);
    m_tileSet = tileSet;
}

void TileMap::Load(std::string file)
{
    std::string filepath= file; 
    std::fstream fs(filepath, std::ios::in);
    if(!fs.is_open())
    {
        printf("Failed to load file at path %s", file.c_str());
    }
   
    std::string substr;
    getline(fs, substr, ',');
    m_mapWidth = stoi(substr);
    getline(fs, substr, ',');
    m_mapHeight = stoi(substr);
    getline(fs, substr, ',');
    m_mapDepth= stoi(substr);
    
    int total = m_mapWidth * m_mapHeight * m_mapDepth;
    m_tileMatrix.resize(total);
    int i = 0;
    while(fs.good() && i < total) 
    {
        getline(fs, substr, ',');
        m_tileMatrix[i++] = (stoi(substr) - 1); //-1 adjusts index to be 0-based
    }
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    if(m_tileSet)
    {
        delete m_tileSet;
    }
    m_tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z)
{
    int i = x + (m_mapWidth * y) + (m_mapWidth * m_mapHeight * z);
    return m_tileMatrix[i];
}

void TileMap::Start(){}

void TileMap::Update(float dt)
{

}

void TileMap::Render()
{
    for(int layer = 0; layer < m_mapDepth; layer++)
    {
        RenderLayer(layer, Camera::m_pos.x(), Camera::m_pos.y());
    }
}

void TileMap::Render(float cameraX, float cameraY)
{
    for(int layer = 0; layer < m_mapDepth; layer++)
    {
        RenderLayer(layer, cameraX, cameraY);
    }
}

void TileMap::RenderLayer(int layer, 
                          float cameraX,
                          float cameraY)
{
    int tileWidth = m_tileSet->GetTileWidth();
    int tileHeight = m_tileSet->GetTileHeight();
    
    int index;

    int offsetX = 0;
    int offsetY = 0; 

    float x = m_associated.m_pos.x() - cameraX;
    float y = m_associated.m_pos.y() - cameraY;

    for(int h = 0; h < m_mapHeight; h++)
    {
        offsetX = 0;
        for(int w = 0; w < m_mapWidth; w++)
        {
            index = At(w, h, layer);
            if(index != -1)
            {
                m_tileSet->RenderTile(index, x+offsetX, y+offsetY);
            }
            offsetX += tileWidth; 
        }
        offsetY += tileHeight;
    }
}

bool TileMap::Is(std::string type)
{
    return (type == "TileMap");
}

int TileMap::GetWidth()
{
    return m_mapWidth;
}

int TileMap::GetHeight()
{
    return m_mapHeight;
}

int TileMap::GetDepth()
{
    return m_mapDepth;
}

