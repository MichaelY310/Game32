#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(vec2 position, double angle, double size, EntityType type, double alpha)
{
    m_Position = position;
    m_Angle = angle;
    m_Size = size;
    m_EntityType = type;
    m_Alpha = alpha;
}