#include "TestGame.h"

TestGame::TestGame(GameEngine *gameEngine)
: Scene(gameEngine)
{
    init();
}

void TestGame::init()
{
    std::cout << "Init called" << std::endl;
    spawnPlayer();
}

void TestGame::spawnPlayer()
{
    std::cout << "player spawned" << std::endl;
}

void TestGame::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sRender();
}

void TestGame::sMovement()
{

}

void TestGame::sLifespan()
{

}

void TestGame::sCollision()
{

}

void TestGame::sAnimation()
{

}

void TestGame::sRender()
{

}

void TestGame::onEnd()
{
    
}

void TestGame::sDebug()
{

}

void TestGame::sDoAction(const Action &action)
{

}