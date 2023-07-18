#include "Intro.h"
#include "TestGame.h"

Intro::Intro(GameEngine *gameEngine) 
    : Scene(gameEngine)
{
    init();

    if (!music.openFromFile("/Users/gillifish/Desktop/GitRepos/PhoenixGameEngine/sounds/pkmn_dp_intro.ogg"))
            return; // error
    music.play();
}

void Intro::init()
{
    registerAction(sf::Keyboard::Enter, "CONTINUE");

    textSetup();
}

void Intro::textSetup()
{
    m_pge_text = m_entityManager.addEntity("ENGINE_TEXT");
    m_pge_text->addComponent<CText>(" Created with\nPhoenix Engine", m_game->assets().getFont("8-BIT-OP"), sf::Color(255, 255, 255, 255), 32);
    m_pge_text->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2));
    m_pge_text->addComponent<CLifespan>(500);

    m_ggs_text = m_entityManager.addEntity("GILLINET_TEXT");
    m_ggs_text->addComponent<CText>("GilliNet Game Studios Presents...", m_game->assets().getFont("8-BIT-OP"), sf::Color(255, 255, 255, 255), 32);
    m_ggs_text->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2));

    auto e = m_entityManager.addEntity("TITLE_TEXT");
    e->addComponent<CText>("  POKEMON\nRevelation", m_game->assets().getFont("8-BIT-OP"), sf::Color(255, 255, 255), 72);
    e->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, (m_game->window().getSize().y / 2) - e->getComponent<CText>().height));

    m_enter_text = m_entityManager.addEntity("TITLE_TEXT");
    m_enter_text->addComponent<CText>("Press enter to start...", m_game->assets().getFont("8-BIT-OP"), sf::Color(255, 255, 255, 255), 32);
    m_enter_text->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, (m_game->window().getSize().y / 2) + 50));
}

void Intro::update()
{
    m_entityManager.update();

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sRender();

    m_currentFrame++;
}

void Intro::sMovement()
{

}

void Intro::sLifespan()
{

    if (m_currentFrame > 600 && m_currentFrame < 1260)
    {
        showText1 = false;
        showText2 = true;
    }

    if (m_currentFrame > 1260)
    {
        showText2 = false;
        showText3 = true;
    }

    if (next && !m_ggs_text->hasComponent<CLifespan>())
    {
        m_ggs_text->addComponent<CLifespan>(500);
    }

    for (auto e : m_entityManager.getEntities())
    {
        if (e->hasComponent<CLifespan>())
        {
            e->getComponent<CLifespan>().remaining--;
            
            if (e->getComponent<CLifespan>().remaining <= 50)
            {
                auto color = e->getComponent<CText>().text.getFillColor();
                e->getComponent<CText>().text.setFillColor(sf::Color(color.r, color.g, color.b, color.a * 0.95));
            }

            if (e->getComponent<CLifespan>().remaining <= 0)
            {
                e->destroy();
                next = true;
            }
        }    
    }
}

void Intro::sCollision()
{

}

void Intro::sAnimation()
{
    if (showText3)
    {
        auto color = m_enter_text->getComponent<CText>().text.getFillColor();
        if (m_currentFrame % 30 == 0 && color.a == 255)
        {
            m_enter_text->getComponent<CText>().text.setFillColor(sf::Color(color.r, color.g, color.b, 0));
        }

        if (m_currentFrame % 30 == 0 && color.a == 0)
        {
            m_enter_text->getComponent<CText>().text.setFillColor(sf::Color(color.r, color.g, color.b, 255));
        }
    }
}

void Intro::sRender()
{
    if (showText1)
    {
        for (auto e : m_entityManager.getEntities("ENGINE_TEXT"))
        {
            auto transform = e->getComponent<CTransform>();
            auto txt = e->getComponent<CText>();
            e->getComponent<CText>().text.setPosition(transform.pos.x - (txt.width / 2), transform.pos.y - (txt.height / 2));
            m_game->window().draw(e->getComponent<CText>().text);
        }
    }

    if (showText2)
    {
        for (auto e : m_entityManager.getEntities("GILLINET_TEXT"))
        {
            auto transform = e->getComponent<CTransform>();
            auto txt = e->getComponent<CText>();
            e->getComponent<CText>().text.setPosition(transform.pos.x - (txt.width / 2), transform.pos.y - (txt.height / 2));
            m_game->window().draw(e->getComponent<CText>().text);
        }
    }

    if (showText3)
    {
        for (auto e : m_entityManager.getEntities("TITLE_TEXT"))
        {
            auto transform = e->getComponent<CTransform>();
            auto txt = e->getComponent<CText>();
            e->getComponent<CText>().text.setPosition(transform.pos.x - (txt.width / 2), transform.pos.y - (txt.height / 2));
            m_game->window().draw(e->getComponent<CText>().text);
        }        
    }
}

void Intro::onEnd()
{
    music.stop();
}

void Intro::sDebug()
{

}

void Intro::sDoAction(const Action &action)
{
    if (action.type() == "START")
    {
        if (action.name() == "CONTINUE")
        {
            m_game->changeScene("START", std::make_shared<TestGame>(m_game));
            onEnd();
        }
    }

    if (action.type() == "END")
    {

    }
}