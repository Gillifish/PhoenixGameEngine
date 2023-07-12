#include "Assets.h"

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