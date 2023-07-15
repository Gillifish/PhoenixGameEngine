#pragma once

#include "Engine/Animation/Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

struct TextureConfig
{
    std::string name;
    std::string path;
};

struct FontConfig
{
    std::string name;
    std::string path;
};

struct AnimationConfig
{
    std::string name;
    std::string texName; 
    size_t frameCount;
    size_t speed;
};

class Assets
{
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, Animation> m_animations;
    std::map<std::string, sf::Sound> m_sounds;
    std::map<std::string, sf::Font> m_fonts;

public:
    void loadFromFile(std::string path);

    void addTexture(std::string name, std::string path);
    void addAnimation(std::string name, Animation anim);
    void addSound(std::string name, std::string path);
    void addFont(std::string name, std::string path);

    sf::Texture &getTexture(std::string name);
    Animation &getAnimation(std::string name);
    sf::Sound &getSound(std::string name);
    sf::Font &getFont(std::string name);
};