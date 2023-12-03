#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(EntityType type, vec2 position, double angle, double size, vec3 color, double alpha, double depth)
{
    m_Position = position;
    m_Angle = angle;
    m_Size = size;
    m_EntityType = type;
    m_Alpha = alpha;
    m_Color = color;
    m_Depth = depth;
}