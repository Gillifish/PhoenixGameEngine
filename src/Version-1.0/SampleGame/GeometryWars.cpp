#include "GeometryWars.h"
#include <iostream>
#include <fstream>

GeometryWars::GeometryWars(const std::string &config)
{
    init(config);
}

void GeometryWars::init(const std::string &path)
{
    // TODO: read in config file here
    //      use the premade PlayerConfig, EnemyConfig, BulletConfig variables
    std::ifstream fin(path);

    // Window initialization
    m_window.create(sf::VideoMode(1280, 720), "Game");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void GeometryWars::setPaused(bool paused)
{
    m_paused = paused;
}

void GeometryWars::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config

    // Creating the player entity
    auto entity = m_entities.addEntity("player");

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->addComponent<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);
    entity->addComponent<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity->addComponent<CInput>();
    entity->addComponent<CCollision>(32.0f);
    m_player = entity;
}

void GeometryWars::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //      the enemy must be spawned completely within the bounds of the window
    srand(time(NULL));

    auto entity = m_entities.addEntity("enemy");

    float ex = getRandNum(0 + 16.0, m_window.getSize().x - 16.0);
    float ey = getRandNum(0 + 16.0, m_window.getSize().y - 16.0);

    entity->addComponent<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

    entity->addComponent<CShape>(16.0f, getRandNum(3, 6), sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    entity->addComponent<CCollision>(16.0f);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

float GeometryWars::getRandNum(int min, int max)
{
    srand(time(NULL));

    return min + (rand() % (1 + max - min));
}

void GeometryWars::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
}

void GeometryWars::sEnemySpawner()
{
    // TODO: code which implements enemy spawning should go here
    //
    //      (use m_currentFrame - m_lastEnemySpawnTime) to determine
    //      how long it has been since last enemy spawned

    if (m_currentFrame - m_lastEnemySpawnTime > 180)
    {
        spawnEnemy();
    }
}

void GeometryWars::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos)
{
    // TODO: Implement the spawning of a bullet which travels toward target
    //       - bullet speed is given as scalar speed
    //       - you must set the velocity by using formula in notes

    auto bullet = m_entities.addEntity("bullet");

    bullet->addComponent<CShape>(16.0f, 32, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    bullet->addComponent<CLifespan>(60);
    bullet->addComponent<CCollision>(16.0f);

    float bAngle = entity->getComponent<CTransform>().pos.angle(mousePos);
    float bDistance = entity->getComponent<CTransform>().pos.dist(mousePos);
    Vec2 bVelocity(bDistance * cos(bAngle), bDistance * sin(bAngle));

    bVelocity.normalize();
    bVelocity = bVelocity * 8;

    bullet->addComponent<CTransform>(Vec2(entity->getComponent<CTransform>().pos.x, entity->getComponent<CTransform>().pos.y), bVelocity, 0.0f);
}

void GeometryWars::sMovement()
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

    for (auto e : m_entities.getEntities())
    {
        e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().velocity.x;
        e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y;
    }
}

void GeometryWars::sCollision()
{
    // Check for play area collision
    for (auto e : m_entities.getEntities())
    {
        if (e->getComponent<CTransform>().pos.x < e->getComponent<CCollision>().radius)
        {
            e->getComponent<CTransform>().pos.x = e->getComponent<CCollision>().radius;
        }

        if (e->getComponent<CTransform>().pos.x > m_window.getSize().x - e->getComponent<CCollision>().radius)
        {
            e->getComponent<CTransform>().pos.x = m_window.getSize().x - e->getComponent<CCollision>().radius;
        }

        if (e->getComponent<CTransform>().pos.y < e->getComponent<CCollision>().radius)
        {
            e->getComponent<CTransform>().pos.y = e->getComponent<CCollision>().radius;
        }

        if (e->getComponent<CTransform>().pos.y > m_window.getSize().y - e->getComponent<CCollision>().radius)
        {
            e->getComponent<CTransform>().pos.y = m_window.getSize().y - e->getComponent<CCollision>().radius;
        }
    }

    // Check for player-enemy collision
    for (auto e : m_entities.getEntities("enemy"))
    {
        float dist = e->getComponent<CTransform>().pos.dist(m_player->getComponent<CTransform>().pos);

        if (dist < e->getComponent<CCollision>().radius + m_player->getComponent<CCollision>().radius)
        {
            e->destroy();

            float mx = m_window.getSize().x / 2.0f;
            float my = m_window.getSize().y / 2.0f;

            m_player->getComponent<CTransform>().pos = Vec2(mx, my);
        }
    }

    // Check for bullet-enemy collision
    for (auto b : m_entities.getEntities("bullet"))
    {
        for (auto e : m_entities.getEntities("enemy"))
        {
            float dist = b->getComponent<CTransform>().pos.dist(e->getComponent<CTransform>().pos);

            if (dist < b->getComponent<CCollision>().radius + e->getComponent<CCollision>().radius)
            {
                b->destroy();
                e->destroy();
            }
        }
    }
}

void GeometryWars::sUserInput()
{
    // TODO: handle user input here
    //      not that you should only be setting the player's input component variables here
    //      you should not implement the players movement logic here
    //      the movement system will read the variables you set in this function

    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_player->getComponent<CInput>().up = true;
                break;
            case sf::Keyboard::S:
                m_player->getComponent<CInput>().down = true;
                break;
            case sf::Keyboard::A:
                m_player->getComponent<CInput>().left = true;
                break;
            case sf::Keyboard::D:
                m_player->getComponent<CInput>().right = true;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                m_player->getComponent<CInput>().up = false;
                break;
            case sf::Keyboard::S:
                m_player->getComponent<CInput>().down = false;
                break;
            case sf::Keyboard::A:
                m_player->getComponent<CInput>().left = false;
                break;
            case sf::Keyboard::D:
                m_player->getComponent<CInput>().right = false;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
            }
        }
    }
}

void GeometryWars::sLifespan()
{
    for (auto e : m_entities.getEntities("bullet"))
    {
        e->getComponent<CLifespan>().remaining--;

        if (e->getComponent<CLifespan>().remaining <= 0)
        {
            e->destroy();
        }
    }
}

void GeometryWars::sRender()
{
    // TODO: change the code below to draw ALL of the entities
    //      sample drawing of the player entity that we have created
    m_window.clear();

    for (auto e : m_entities.getEntities())
    {
        e->getComponent<CShape>().circle.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
        e->getComponent<CTransform>().angle += 1.0f;
        e->getComponent<CShape>().circle.setRotation(e->getComponent<CTransform>().angle);
    }

    // draw the entity's sf::CircleShape

    for (auto e : m_entities.getEntities())
    {
        m_window.draw(e->getComponent<CShape>().circle);
    }

    m_window.display();
}

void GeometryWars::run()
{
    while (m_running)
    {
        m_entities.update();

        sEnemySpawner();
        sLifespan();
        sMovement();
        sCollision();
        sUserInput();
        sRender();

        m_currentFrame++;
    }
}