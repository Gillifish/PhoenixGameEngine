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