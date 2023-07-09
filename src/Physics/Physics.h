#include <iostream>
#include "Entity.h"

class Physics
{
public:
    Vec2 Physics::getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 Physics::getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};