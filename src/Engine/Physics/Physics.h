#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine/Entity/Entity.h"

class Physics
{
public:
    bool isCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);

    // isIntersect compares two lines but I'm not sure how to do this yet
    bool isIntersect();
    // same with isInside()
    bool isInside();


    Vec2 getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};