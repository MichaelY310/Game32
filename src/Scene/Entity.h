#pragma once
#include "Render/DataTypes.h"

enum class EntityType
{
    NONE = 0,
    PLAYER,
    BOSS,
    PLAYER_BULLET,
    BOSS_BIG_BULLET,
    BOSS_SMALL_BULLET,

};

class Entity
{
public:
    Entity();
    Entity(vec2 position, double angle, double size, EntityType type, double alpha=1.0f);


    vec2 m_Position = vec2(0.0f, 0.0f);
    double m_Angle = 90.0f;
    double m_Size = 0.1f;
    double m_Alpha = 1.0f;
    
    EntityType m_EntityType = EntityType::NONE;

};