#include "Tilemap.h"

Tilemap::Tilemap(std::string texTag, Vec2 size, std::string filePath) : 
    m_texTag(texTag), 
    m_tileSize(size),
    m_mapFilePath(filePath)
{
    loadMapFile();
}

void Tilemap::loadMapFile()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    auto path = currentDir.string() + "/" + m_mapFilePath;

    std::fstream inputFile(path);
    if (!inputFile)
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;

    while(std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        Tile tile;
        iss >> tile.tag;
        iss >> tile.textureX;
        iss >> tile.textureY;
        iss >> tile.renderX;
        iss >> tile.renderY;
        iss >> tile.collision;

        m_tMap.push_back(tile);
    }

    inputFile.close();
}

void Tilemap::loadMap(EntityManager &eManager, Assets &assets)
{
    for (auto tile : getTileMap())
    {
        auto e = eManager.addEntity(tile.tag);
        e->addComponent<CSprite>();
        auto &sprite = e->getComponent<CSprite>().sprite;
        sprite.setTexture(assets.getTexture(getTextureTag()));
        Vec2 v(gridToPixel(tile.textureX, tile.textureY));
        sprite.setTextureRect(sf::IntRect(v.x, v.y, getTileSize().x, getTileSize().y));
        sprite.setOrigin(getTileSize().x / 2, getTileSize().y / 2);

        auto pos = gridToMidPixel(tile.renderX, tile.renderY);
        sprite.setPosition(pos.x, pos.y);
    }
}

void Tilemap::render(EntityManager &eManager, sf::RenderWindow &window)
{
    for (auto e : eManager.getEntities("TILEMAP"))
    {
        window.draw(e->getComponent<CSprite>().sprite);
    }
}

void Tilemap::setTexturePath(std::string &path)
{
    m_mapFilePath = path;
}

void Tilemap::setTileTag(std::string &tag)
{
    m_tileTag = tag;
}

Vec2 Tilemap::getTileSize()
{
    return m_tileSize;
}

TileMap Tilemap::getTileMap()
{
    return m_tMap;
}

std::string Tilemap::getTileTag()
{
    return m_tileTag;
}

std::string Tilemap::getTextureTag()
{
    return m_texTag;
}

Vec2 Tilemap::gridToPixel(float gridX, float gridY)
{
    return Vec2(gridX * m_tileSize.x, gridY * m_tileSize.y);
}

Vec2 Tilemap::gridToMidPixel(float gridX, float gridY)
{
    float pixelX = gridX * m_tileSize.x;
    float pixelY = gridY * m_tileSize.y;

    return Vec2(pixelX + (m_tileSize.x / 2), pixelY + (m_tileSize.y / 2));
}