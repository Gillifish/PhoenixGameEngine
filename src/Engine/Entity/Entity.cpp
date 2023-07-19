#include "Entity.h"

Entity::Entity(const size_t &id, const std::string &tag) : m_id(id), m_tag(tag)
{
    m_components = std::make_tuple(
        CTransform(),
        CLifespan(),
        CInput(),
        CBoundingBox(),
        CAnimation(),
        CGravity(),
        CState(),
        CShape(),
        CCollision(),
        CText(),
        CSprite(),
        CDirection2D()
    );
}

void Entity::destroy()
{
    m_active = false;
}

const std::string &Entity::tag() const
{
    return m_tag;
}

const size_t Entity::id() const
{
    return m_id;
}

bool Entity::isActive() const
{
    return m_active;
}