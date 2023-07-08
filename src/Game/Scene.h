#include <iostream>

#include "Entity/EntityManager.h"

class Scene
{
    GameEngine game;
    EntityManager entities;
    int currentFrame;
    std::map<int, std::string> actionMap;
    bool paused;
    bool hasEnded;

public:
    virtual void update() = 0;
    virtual void sDoAction(std::string action) = 0;
    virtual void sRender() = 0;

    void simulate(int i);
    void doAction(std::string action);
    void registerAction(std::string action);
};