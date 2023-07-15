#pragma once

#include "Engine/Entity/EntityManager.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Game/GameEngine.h"
#include <SFML/Graphics.hpp>

class Intro : public Scene
{
    std::shared_ptr<Entity> m_pge_text;
    std::shared_ptr<Entity> m_ggs_text;
    std::shared_ptr<Entity> m_enter_text;
    
    sf::Music music;
    bool showText1 = true;
    bool showText2 = false;
    bool showText3 = false;
    bool next = false;

    //int animationFrameCount = 0;

    void init();
    void textSetup();

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
    Intro(GameEngine *gameEngine);
    void update();
};