#include <iostream>

#include "Assets.h"
#include "Scene.h"
#include <SFML/Graphics.hpp>

class GameEngine
{
    std::map<std::string, Scene> scenes;
    sf::RenderWindow window;
    Assets assets;
    std::string currentScene;
    bool running;

    void init();
    Scene *currentScene();

public:
    void run();
    void update();
    void quit();
    void changeScene(Scene scene);
    Assets &getAssets();
    sf::RenderWindow &window();
    void sUserInput();
};