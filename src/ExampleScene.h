#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Game/GameEngine.h"
#include "Engine/Tilemap/Tilemap.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Class used for testing various functionality of the game engine
class ExampleScene : public Scene
{
    std::shared_ptr<Entity> m_player;
    sf::Music m_music;
    sf::View m_camera;
    float m_tileWidth;
    float m_tileHeight;
    Tilemap m_tilemap;

    void init();

    void bottomLayer();
    void middleLayer();
    void topLayer();
    void spawnPlayer();
    void spawnMapEntities();
    void sAnimation();
    void sMovement();
    void sCamera();
    void sLifespan();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(const Action &action);
    void sDebug();
    void onEnd();

    Vec2 gridToMidPixel(float gridX, float gridY, float offsetX = 0, float offsetY = 0);
    void renderMap();

public:
    ExampleScene(GameEngine *gameEngine);
    void update();
};