#pragma once

#include <iostream>

#include "Assets.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Scene_Play.h"
#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
    sf::RenderWindow m_window;
    Assets m_assets;
    std::string m_currentScene;
    SceneMap m_sceneMap;
    size_t m_simulationSpeed = 1;
    bool m_running = true;
    sf::Color m_background = {0, 0, 0};

    void init(const std::string &path);
    void update();

    void sUserInput();

    std::shared_ptr<Scene> currentScene();

public:
    GameEngine(const std::string &path);

    void changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
    void quit();
    void run();

    const size_t width() const;
    const size_t height() const;

    sf::RenderWindow &window();
    Assets &assets();
    bool isRunning();
    void setBackground(sf::Color &color);
};