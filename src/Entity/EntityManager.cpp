#include "EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(e);

    return e;
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    m_toAdd.clear();

    removeDeadEntities(m_entities);

    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    // ChatGPT saved my ass

    vec.erase(
        std::remove_if(vec.begin(), vec.end(),
                       [&](std::shared_ptr<Entity> &e)
                       {
                           return !e->isActive();
                       }),
        vec.end());
}

const EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}