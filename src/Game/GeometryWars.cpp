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

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity->cInput = std::make_shared<CInput>();
    entity->cCollision = std::make_shared<CCollision>(32.0f);
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

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(16.0f, getRandNum(3, 6), sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    entity->cCollision = std::make_shared<CCollision>(16.0f);

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

    bullet->cShape = std::make_shared<CShape>(16.0f, 32, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
    bullet->cLifespan = std::make_shared<CLifespan>(60);
    bullet->cCollision = std::make_shared<CCollision>(16.0f);

    float bAngle = entity->cTransform->pos.angle(mousePos);
    float bDistance = entity->cTransform->pos.dist(mousePos);
    Vec2 bVelocity(bDistance * cos(bAngle), bDistance * sin(bAngle));

    bVelocity.normalize();
    bVelocity = bVelocity * 8;

    bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), bVelocity, 0.0f);
}

void GeometryWars::sMovement()
{
    // TODO: implement all entity movement in this function
    //      you should read the m_player->cInput component to determine if the player is moving

    m_player->cTransform->velocity = {0, 0};

    // Implement player movement
    if (m_player->cInput->up)
    {
        m_player->cTransform->velocity.y = -5;
    }

    if (m_player->cInput->down)
    {
        m_player->cTransform->velocity.y = 5;
    }

    if (m_player->cInput->left)
    {
        m_player->cTransform->velocity.x = -5;
    }

    if (m_player->cInput->right)
    {
        m_player->cTransform->velocity.x = 5;
    }

    // m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    // m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

    for (auto e : m_entities.getEntities())
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
}

void GeometryWars::sCollision()
{
    // Check for play area collision
    for (auto e : m_entities.getEntities())
    {
        if (e->cTransform->pos.x < e->cCollision->radius)
        {
            e->cTransform->pos.x = e->cCollision->radius;
        }

        if (e->cTransform->pos.x > m_window.getSize().x - e->cCollision->radius)
        {
            e->cTransform->pos.x = m_window.getSize().x - e->cCollision->radius;
        }

        if (e->cTransform->pos.y < e->cCollision->radius)
        {
            e->cTransform->pos.y = e->cCollision->radius;
        }

        if (e->cTransform->pos.y > m_window.getSize().y - e->cCollision->radius)
        {
            e->cTransform->pos.y = m_window.getSize().y - e->cCollision->radius;
        }
    }

    // Check for player-enemy collision
    for (auto e : m_entities.getEntities("enemy"))
    {
        float dist = e->cTransform->pos.dist(m_player->cTransform->pos);

        if (dist < e->cCollision->radius + m_player->cCollision->radius)
        {
            e->destroy();

            float mx = m_window.getSize().x / 2.0f;
            float my = m_window.getSize().y / 2.0f;

            m_player->cTransform->pos = Vec2(mx, my);
        }
    }

    // Check for bullet-enemy collision
    for (auto b : m_entities.getEntities("bullet"))
    {
        for (auto e : m_entities.getEntities("enemy"))
        {
            float dist = b->cTransform->pos.dist(e->cTransform->pos);

            if (dist < b->cCollision->radius + e->cCollision->radius)
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
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = true;
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
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::S:
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::A:
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::D:
                m_player->cInput->right = false;
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
        e->cLifespan->remaining--;

        if (e->cLifespan->remaining <= 0)
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
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
    }

    // draw the entity's sf::CircleShape

    for (auto e : m_entities.getEntities())
    {
        m_window.draw(e->cShape->circle);
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