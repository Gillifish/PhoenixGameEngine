#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::init(const std::string &path)
{
    // TODO: read in config file here
    //      use the premade PlayerConfig, EnemyConfig, BulletConfig variables
    std::ifstream fin(path);

    // Window initialization
    m_window.create(sf::VideoMode(1280, 720), "Game");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::setPaused(bool paused)
{
    m_paused = paused;
}

void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config

    // Creating the player entity
    auto entity = m_entities.addEntity("player");

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f), 0.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity->cInput = std::make_shared<CInput>();
    m_player = entity;
}

void Game::spawnEnemy()
{
    // TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
    //      the enemy must be spawned completely within the bounds of the window

    auto entity = m_entities.addEntity("enemy");

    float ex = rand() % m_window.getSize().x;
    float ey = rand() % m_window.getSize().y;

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(16.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

    // record when the most recent enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
}

void Game::sEnemySpawner()
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

void Game::sMovement()
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

    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sCollision()
{
}

void Game::sUserInput()
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
    }
}

void Game::sRender()
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

void Game::run()
{
    while (m_running)
    {
        m_entities.update();

        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();

        m_currentFrame++;
    }
}