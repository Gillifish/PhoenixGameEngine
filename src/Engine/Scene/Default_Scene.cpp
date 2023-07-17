#include "Engine/Scene/Default_Scene.h"

#include <iostream>

Default_Scene::Default_Scene(GameEngine *gameEngine)
: Scene(gameEngine)
{
    init("");
}

Default_Scene::Default_Scene(GameEngine *gameEngine, const std::string &levelPath)
    : Scene(gameEngine)
    , m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Default_Scene::init(const std::string &levelPath)
{

}

void Default_Scene::spawnPlayer()
{
    // NOTE: implement after finishing Scene.h, shown in lecture 11 at 55:31/1:35:36
    m_player = m_entityManager.addEntity("player");
}

void Default_Scene::sMovement()
{
}

void Default_Scene::sLifespan()
{
}

void Default_Scene::sEnemySpawner()
{

}

void Default_Scene::sCollision()
{
}

void Default_Scene::sAnimation()
{
}

void Default_Scene::sDebug()
{

}

void Default_Scene::sRender()
{
}

void Default_Scene::sDoAction(const Action &action)
{

}

void Default_Scene::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sRender();
}

void Default_Scene::onEnd()
{
}