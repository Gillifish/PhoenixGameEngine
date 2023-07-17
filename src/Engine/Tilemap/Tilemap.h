#pragma once

#include <iostream>

#include "Engine/Game/GameEngine.h"
#include "Engine/Vec2/Vec2.h"
#include "Engine/Entity/EntityManager.h"
#include "Engine/Scene/Scene.h"
#include <SFML/Graphics.hpp>

struct Tile
{
    std::string tag;
    float textureX;
    float textureY;
    float renderX;
    float renderY;
    bool collision = false;
};

typedef std::vector<Tile> TileMap;

class Tilemap
{

    Vec2 m_tileSize = { 32, 32 };
    std::string m_mapFilePath = "";
    std::string m_texTag = "none";
    std::string m_tileTag = "TILEMAP";
    TileMap m_tMap;
    
    void setTexturePath(std::string &path);
    void setTileTag(std::string &tag);
    void loadMap();


public:
    Tilemap() = default;
    Tilemap(std::string texTag, Vec2 size, std::string path);

    Vec2 getTileSize();
    TileMap getTileMap();
    std::string getTextureTag();
    std::string getTileTag();
    Vec2 gridToPixel(float gridX, float gridY);
    Vec2 gridToMidPixel(float gridX, float gridY);

};