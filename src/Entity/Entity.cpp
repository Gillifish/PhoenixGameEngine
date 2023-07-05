#include "Entity.h"

void Entity::destroy() { m_active = false; }

const std::string &Entity::tag() const { return m_tag; }

const size_t Entity::id() const { return m_id; }

bool Entity::isActive() const { return m_active; }