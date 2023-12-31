#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(EntityType type, vec2 position, double angle, vec2 size, vec3 color, double alpha, double depth, std::shared_ptr<Texture> texture)
{
    m_Position = position;
    m_Angle = angle;
    m_Size = size;
    m_EntityType = type;
    m_Alpha = alpha;
    m_Color = color;
    m_Depth = depth;
    m_Texture = texture;
}