#include "Assets.h"

void Assets::loadFromFile(std::string path)
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    path = currentDir.string() + "/" + path;

    std::fstream inputFile(path);
    if (!inputFile)
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;

    while(std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string token;

        iss >> token;

        if (token == "Texture")
        {
            TextureConfig tConfig;
            iss >> tConfig.name;
            iss >> tConfig.path;

            addTexture(tConfig.name, tConfig.path); 
        }

        if (token == "Animation")
        {
            AnimationConfig aConfig;
            iss >> aConfig.name;
            iss >> aConfig.texName;
            iss >> aConfig.frameCount;
            iss >> aConfig.speed;

            addAnimation(aConfig.name, Animation(aConfig.name, getTexture(aConfig.texName), aConfig.frameCount, aConfig.speed));
        }

        if (token == "Font")
        {
            FontConfig fConfig;
            iss >> fConfig.name;
            iss >> fConfig.path;

            addFont(fConfig.name, fConfig.path);
        }
    }

    inputFile.close();
}

void Assets::addTexture(std::string name, std::string path)
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    sf::Texture tex;
    if (!tex.loadFromFile(currentDir.string() + "/" + path))
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        return;
    }

    m_textures[name] = tex;
}

// TODO: buffer is being destroyed after function end, fix this
void Assets::addSound(std::string name, std::string path)
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(currentDir.string() + "/" + path))
    {
        std::cout << "Failed to load sound: " << path << std::endl;
        return;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    m_sounds[name] = sound;
}

void Assets::addFont(std::string name, std::string path)
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    sf::Font font;
    if (!font.loadFromFile(currentDir.string() + "/" + path))
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