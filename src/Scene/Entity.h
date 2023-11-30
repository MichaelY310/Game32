#pragma once
#include "Render/DataTypes.h"

enum class EntityType
{
    NONE = 0,
    PLAYER,
    ENEMY,
    BOSS,
    PLAYER_BULLET,
    ENEMY_BULLET,

};

class Entity
{
public:
    Entity();
    Entity(vec2 position, double angle, double size, EntityType type);


    vec2 m_Position = vec2(0.0f, 0.0f);
    double m_Angle = 90.0f;
    double m_Size = 0.1f;
    
    EntityType m_EntityType = EntityType::NONE;

};