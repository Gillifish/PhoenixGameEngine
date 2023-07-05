#pragma once
#include <iostream>

class Vec2
{
public:
    float x = 0.0;
    float y = 0.0;

    Vec2(float xin, float yin);
    bool operator == (const Vec2& rhs) const;
    bool operator != (const Vec2& rhs) const;
    Vec2 operator += (const Vec2& rhs) const;
    Vec2 operator -= (const Vec2& rhs) const;
    Vec2 operator *= (const Vec2& rhs) const;
    Vec2 operator /= (const Vec2& rhs) const;
    Vec2 operator + (const Vec2& rhs) const;
    Vec2 operator - (const Vec2& rhs) const;
    Vec2 operator * (const Vec2& rhs) const;
    Vec2 operator * (const int i) const;
    Vec2 operator / (const Vec2& rhs) const;
    float dist(const Vec2& rhs) const;
    void normalize();
    double length();
    void print();
};