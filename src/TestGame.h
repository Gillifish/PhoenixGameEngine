#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Game/GameEngine.h"
#include <SFML/Graphics.hpp>

// Class used for testing various functionality of the game engine
class TestGame : public Scene
{
    std::shared_ptr<Entity> m_player;
    sf::Music music;

    void init();

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

    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

public:
    TestGame(GameEngine *gameEngine);
    void update();
};