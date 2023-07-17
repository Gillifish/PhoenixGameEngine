#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Game/GameEngine.h"
#include <SFML/Graphics.hpp>

class Default_Scene : public Scene
{
    std::string m_levelPath;
    std::shared_ptr<Entity> m_player;
    PlayerConfig playerConfig;

    void init(const std::string &levelPath);

    void spawnPlayer();
    void sAnimation();
    void sMovement();
    void sLifespan();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(const Action &action);
    void sDebug();
    void onEnd();

public:
    Default_Scene(GameEngine *gameEngine);
    Default_Scene(GameEngine *gameEngine, const std::string &levelPath);
    //Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
    void update();
};