#include "GameEngine.h"
#include "Engine/Scene/Scene_Play.h"
#include "TestGame.h"
#include "Intro.h"

#include <iostream>

GameEngine::GameEngine(const std::string &path)
{
    init(path);
}

void GameEngine::init(const std::string &path)
{
    m_assets.loadFromFile(path);

    m_window.create(sf::VideoMode(1200, 768), "Phoenix Engine");
    m_window.setFramerateLimit(60);

    changeScene("INTRO", std::make_shared<Intro>(this));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

// TODO
void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    auto it = m_sceneMap.find(sceneName);

    if (it == m_sceneMap.end())
    {
        m_sceneMap[sceneName] = scene;
    }

    m_currentScene = sceneName;
}

bool GameEngine::isRunning()
{
    return m_running & m_window.isOpen();
}

sf::RenderWindow &GameEngine::window()
{
    return m_window;
}

void GameEngine::run()
{
    while (isRunning())
    {
        m_window.clear(m_background);
        update();
        m_window.display();
    }
}

void GameEngine::update()
{
    currentScene()->update();
    sUserInput();
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            quit();
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // if the current scene does not have an action associated with this key, skip the event
            if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }

            // determine start or end action by whether it was key press or release
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            // look up the action and send the action to the scene
            currentScene()->sDoAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
        }
    }
}

void GameEngine::quit()
{
    m_running = false;
}

Assets &GameEngine::assets()
{
    return m_assets;
}

const size_t GameEngine::width() const
{
    return m_window.getSize().x;
}

const size_t GameEngine::height() const
{
    return m_window.getSize().y;
}

void GameEngine::setBackground(sf::Color &color)
{
    m_background = color;
}