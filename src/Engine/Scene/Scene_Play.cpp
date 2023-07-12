#include "Scene_Play.h"
#include <iostream>

Scene_Play::Scene_Play(GameEngine *gameEngine)
: Scene(gameEngine)
{
    init("");
}

Scene_Play::Scene_Play(GameEngine *gameEngine, const std::string &levelPath)
    : Scene(gameEngine)
    , m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Scene_Play::init(const std::string &levelPath)
{

}

void Scene_Play::spawnPlayer()
{
    // NOTE: implement after finishing Scene.h, shown in lecture 11 at 55:31/1:35:36
    m_player = m_entityManager.addEntity("player");
}

void Scene_Play::sMovement()
{
}

void Scene_Play::sLifespan()
{
}

void Scene_Play::sEnemySpawner()
{

}

void Scene_Play::sCollision()
{
}

void Scene_Play::sAnimation()
{
}

void Scene_Play::sDebug()
{

}

void Scene_Play::sRender()
{
}

void Scene_Play::sDoAction(const Action &action)
{

}

void Scene_Play::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sRender();
}

void Scene_Play::onEnd()
{
}