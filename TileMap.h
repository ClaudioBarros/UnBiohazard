#pragma once    

#include "Component.h"
#include <vector>

struct TileSet;

struct TileMap : Component
{
private:   
    std::vector<int> m_tileMatrix; 
    TileSet* m_tileSet;
    int m_mapWidth;
    int m_mapHeight;
    int m_mapDepth;

public:
    TileMap(GameObject& associated, 
            std::string file,
            TileSet* tileSet);

    void Load(std::string file);
    
    void SetTileSet(TileSet* tileSet);

    int& At(int x, int y, int z = 0);

    void Start();
    void Update(float dt);
    void Render();
    void Render(float cameraX, float cameraY);

    void RenderLayer(int layer, 
                     float cameraX = 0.0f,
                     float cameraY = 0.0f);
    
    bool Is(std::string type);
    int GetWidth();
    int GetHeight();
    int GetDepth();
};
