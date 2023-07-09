#include "GameEngine.h"
#include "Assets.h"
#include "Scene/Scene_Play.h"

#include <iostream>

GameEngine::GameEngine(const std::string &path)
{
    init(path);
}

void GameEngine::init(const std::string &path)
{
    // TODO: m_assets.loadFromFile(path)

    m_window.create(sf::VideoMode(1200, 768), "Definitaly Not Mario");
    m_window.setFramerateLimit(60);

    //changeScene("MENU", std::make_shared<Scene_Play>(this), false);
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

// TODO
void changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{

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
        update();
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
    }
}

void GameEngine::quit()
{
    m_running = false;
}

const Assets &GameEngine::assets() const
{
    return m_assets;
}