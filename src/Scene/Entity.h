#pragma once
#include "Render/DataTypes.h"
#include "Render/Texture.h"

enum class EntityType
{
    NONE = 0,
    MENU,
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
    Entity(EntityType type, vec2 position, double angle, double size, vec3 color, double alpha, double depth, std::shared_ptr<Texture> texture = nullptr);

    EntityType m_EntityType = EntityType::NONE;

    vec2 m_Position = vec2(0.0f, 0.0f);
    double m_Angle = 90.0f;
    double m_Size = 0.1f;
    vec3 m_Color = { 1.0f, 1.0f, 1.0f };
    double m_Alpha = 1.0f;
    double m_Depth = 0.0f;
    std::shared_ptr<Texture> m_Texture;
};