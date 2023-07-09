#include <iostream>
#include "Vec2/Vec2.h"
#include <SFML/Graphics.hpp>

class Animation
{
    sf::Sprite m_sprite;
    size_t m_frameCount = 1;
    size_t m_currentFrame = 0;
    size_t m_speed = 0;
    Vec2 m_size = { 1, 1 };
    std::string m_name = "name";

public:
    Animation();
    Animation(const std::string &name, const sf::Texture &t);
    Animation(const std::string &name, const sf::Texture &t, size_t frameCount, size_t speed);

    void update();
    bool hasEnded() const;
    const std::string &getName() const;
    const Vec2 &getSize() const;
    sf::Sprite &getSprite();
};