#pragma once

#include <iostream>

#include "Engine/Entity/EntityManager.h"
#include "Engine/Action/Action.h"

class GameEngine;
typedef std::map<int, std::string> ActionMap;

class Scene
{
protected:
    GameEngine *m_game = nullptr;
    EntityManager m_entityManager;
    ActionMap m_actionMap;
    bool m_paused = false;
    bool m_hasEnded = false;
    size_t m_currentFrame = 0;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

public:
    //Scene();
    Scene(GameEngine *gameEngine);

    virtual void update() = 0;
    virtual void sDoAction(const Action &action) = 0;
    virtual void sRender() = 0;

    //void sSimulate(const size_t frames);
    void registerAction(int inputKey, const std::string &actionName);

    size_t currentFrame() const;

    bool hasEnded() const;
    const ActionMap &getActionMap() const;
};