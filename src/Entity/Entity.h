#pragma once

#include "Components/Components.h"
#include <memory>
#include <string>

class Entity
{
    friend class EntityManager;

    const size_t m_id = 0;
    const std::string m_tag = "Default";
    bool m_active = true;

    Entity(const std::string &tag, size_t id) : m_tag(tag), m_id(id) {}

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;
    void destroy();
    const std::string &tag() const;
    const size_t id() const;
    bool isActive() const;
};