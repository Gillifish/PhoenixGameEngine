#include "Assets.h"

void Assets::addTexture(std::string name, std::string path)
{
    sf::Texture tex;
    if (!tex.loadFromFile(path))
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return;
    }

    m_textures[name] = tex;
}

void Assets::addFont(std::string name, std::string path)
{
    sf::Font font;
    if (!font.loadFromFile(path))
    {
        std::cout << "Failed to load font: " << path << std::endl;
        return;
    }

    m_fonts[name] = font;
}

void Assets::addAnimation(std::string name, Animation anim)
{
    m_animations[name] = anim;
}



sf::Texture &Assets::getTexture(std::string name)
{
    return m_textures[name];
}

Animation &Assets::getAnimation(std::string name)
{
    return m_animations[name];
}

sf::Sound &Assets::getSound(std::string name)
{
    return m_sounds[name];
}

sf::Font &Assets::getFont(std::string name)
{
    return m_fonts[name];
}