#pragma once

#include "Vec2/Vec2.h"
#include <SFML/Graphics.hpp>

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 pos = {0.0, 0.0};
    Vec2 prevPos = {0.0, 0.0};
    Vec2 scale = {1.0, 1.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0;

    CTransform() {}
    CTransform(const Vec2 &p) {}
    CTransform(const Vec2 &p, const Vec2 &v, float a)
        : pos(p), velocity(v), angle(a) {}
};

class CShape : public Component
{
public:
    sf::CircleShape circle;

    CShape() {}
    CShape(float radius, int points, const sf::Color &fill,
           const sf::Color &outline, float thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision : public Component
{
public:
    float radius = 0;
    CCollision() {}
    CCollision(float r)
        : radius(r) {}
};

class CScore : Component
{
public:
    int score = 0;
    CScore() {}
    CScore(int s)
        : score(s) {}
};

class CLifespan : public Component
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan() {}
    CLifespan(int total)
        : remaining(total), total(total) {}
};

class CInput : public Component
{
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;

    CInput() {}
};

class CBoundingBox : public Component
{
public:
    CBoundingBox() {}
};

class CAnimation : public Component
{
public:
    CAnimation() {}
};

class CGravity : public Component
{
public:
    CGravity() {}
};

class CState : public Component
{
public:
    CState() {}
};