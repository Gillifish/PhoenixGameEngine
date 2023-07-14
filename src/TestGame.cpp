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
    e->addComponent<CState>("IDLE_DOWN");
    e->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_DOWN"), true);
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
        m_player->getComponent<CTransform>().velocity.y = -3;
    }
    else if (m_player->getComponent<CInput>().down)
    {
        m_player->getComponent<CTransform>().velocity.y = 3;
        m_player->getComponent<CState>().state = "WALK_DOWN";
    }
    else if (m_player->getComponent<CInput>().left)
    {
        m_player->getComponent<CTransform>().velocity.x = -3;
    }
    else if (m_player->getComponent<CInput>().right)
    {
        m_player->getComponent<CTransform>().velocity.x = 3;
    }
    else if (m_player->getComponent<CTransform>().velocity == Vec2(0.0f, 0.0f))
    {
        m_player->getComponent<CState>().state = "IDLE_DOWN";
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
    if (m_player->getComponent<CState>().state == "IDLE_DOWN" && m_player->getComponent<CAnimation>().animation.getName() == "WALK_DOWN")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_DOWN"));
        m_player->getComponent<CAnimation>().repeat = false;
    }

    if (m_player->getComponent<CState>().state == "WALK_DOWN")
    {
        m_player->getComponent<CAnimation>().repeat = true;
    }

    if (m_player->getComponent<CAnimation>().repeat)
    {
        m_player->getComponent<CAnimation>().animation.update();
    }
}

void TestGame::sRender()
{
    for (auto e : m_entityManager.getEntities())
    {
        auto &transform = e->getComponent<CTransform>();

        if (e->hasComponent<CAnimation>())
        {
            auto &animation = e->getComponent<CAnimation>().animation;
            animation.getSprite().setRotation(transform.angle);
            animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
            animation.getSprite().setScale(transform.scale.x, transform.scale.y);
            m_game->window().draw(animation.getSprite());
        }

        if (e->hasComponent<CBoundingBox>() && e->getComponent<CBoundingBox>().active)
        {
            auto &bBox = e->getComponent<CBoundingBox>();
            bBox.rect.setPosition(transform.pos.x, transform.pos.y);
            m_game->window().draw(bBox.rect);

        }
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
        }
        else if (action.name() == "DEBUG")
        {
            for (auto e : m_entityManager.getEntities())
            {
                if (e->getComponent<CBoundingBox>().has)
                {
                    if (e->getComponent<CBoundingBox>().active)
                    {
                        e->getComponent<CBoundingBox>().active = false;
                    }
                    else
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