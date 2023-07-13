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
    auto e = m_entityManager.addEntity("player");
    std::cout << m_game->width() / 2 << std::endl;
    e->addComponent<CTransform>().pos = Vec2(m_game->width() / 2, m_game->height() / 2);
    e->addComponent<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

    m_player = e;
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
    for (auto e : m_entityManager.getEntities("player"))
    {
        e->getComponent<CShape>().circle.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
        m_game->window().draw(e->getComponent<CShape>().circle);
    }
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