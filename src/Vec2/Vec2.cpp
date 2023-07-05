#include "Vec2.h"

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{
}

bool Vec2::operator==(const Vec2 &rhs) const
{
    if (x == rhs.x && y == rhs.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Vec2::operator!=(const Vec2 &rhs) const
{
    if (x != rhs.x && y != rhs.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vec2 Vec2::operator+=(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-=(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*=(const Vec2 &rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/=(const Vec2 &rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2 &rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*(const int i) const
{
    return Vec2(x * i, y * i);
}

Vec2 Vec2::operator/(const Vec2 &rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

float Vec2::dist(const Vec2 &rhs) const
{
    return sqrt(pow(rhs.x - x, 2) + pow(rhs.y - y, 2));
}

void Vec2::normalize()
{
    double len = length();

    x = x / len;
    y = y / len;
}

double Vec2::length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vec2::print()
{
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}