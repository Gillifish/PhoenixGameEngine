#include "TestGame.h"

TestGame::TestGame(GameEngine *gameEngine)
    : Scene(gameEngine)
{
    init();
}

void TestGame::init()
{
    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::G, "DEBUG");
    spawnPlayer();
}

void TestGame::spawnPlayer()
{
    auto e = m_entityManager.addEntity("player");
    e->addComponent<CTransform>().pos = Vec2(m_game->width() / 2, m_game->height() / 2);
    e->addComponent<CSprite>(m_game->assets().getTexture("player"), sf::IntRect(0, 0, 32, 48));
    e->addComponent<CBoundingBox>(Vec2(32, 48));

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
    // TODO: implement all entity movement in this function
    //      you should read the m_player->cInput component to determine if the player is moving

    m_player->getComponent<CTransform>().velocity = {0.0, 0.0};

    // Implement player movement
    if (m_player->getComponent<CInput>().up)
    {
        m_player->getComponent<CTransform>().velocity.y = -5;
    }

    if (m_player->getComponent<CInput>().down)
    {
        m_player->getComponent<CTransform>().velocity.y = 5;
    }

    if (m_player->getComponent<CInput>().left)
    {
        m_player->getComponent<CTransform>().velocity.x = -5;
    }

    if (m_player->getComponent<CInput>().right)
    {
        m_player->getComponent<CTransform>().velocity.x = 5;
    }

    for (auto e : m_entityManager.getEntities())
    {
        e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().velocity.x;
        e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y;
    }
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
        e->getComponent<CSprite>().sprite.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
        e->getComponent<CBoundingBox>().rect.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
        
        if (e->getComponent<CBoundingBox>().active)
        {
            m_game->window().draw(e->getComponent<CBoundingBox>().rect);
        }

        m_game->window().draw(e->getComponent<CSprite>().sprite);
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
    if (action.type() == "START")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = true;
        }
        else if (action.name() == "DOWN")
        {
            m_player->getComponent<CInput>().down = true;
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = true;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = true;
        } else if (action.name() == "DEBUG")
        {
            for (auto e : m_entityManager.getEntities())
            {
                if (e->getComponent<CBoundingBox>().has)
                {
                    if (e->getComponent<CBoundingBox>().active)
                    {
                        e->getComponent<CBoundingBox>().active = false;
                    } else 
                    {   
                        e->getComponent<CBoundingBox>().active = true;
                    }
                }
            }
        }
    }

    if (action.type() == "END")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = false;
        }
        else if (action.name() == "DOWN")
        {
            m_player->getComponent<CInput>().down = false;
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = false;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = false;
        }
    }
}