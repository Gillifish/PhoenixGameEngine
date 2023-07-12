#include "Scene.h"

Scene::Scene(GameEngine *gameEngine)
{
    m_game = gameEngine;
}

void Scene::registerAction(int inputKey, const std::string &actionName)
{
    m_actionMap[inputKey] = actionName;
}

const ActionMap &Scene::getActionMap() const
{
    return m_actionMap;
}

size_t Scene::currentFrame() const
{
    return m_currentFrame;
}

void Scene::setPaused(bool paused)
{
    m_paused = paused;
}

bool Scene::hasEnded() const
{
    return m_hasEnded;
}