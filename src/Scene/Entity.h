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
    LEADERBOARD,

};

class Entity
{
public:
    Entity();
    Entity(EntityType type, vec2 position, double angle, vec2 size, vec3 color, double alpha, double depth, std::shared_ptr<Texture> texture = nullptr);

    EntityType m_EntityType = EntityType::NONE;

    vec2 m_Position = vec2(0.0f, 0.0f);
    double m_Angle = 90.0f;
    vec2 m_Size = { 0.1, 0.1 };
    vec3 m_Color = { 1.0f, 1.0f, 1.0f };
    double m_Alpha = 1.0f;
    double m_Depth = 0.0f;
    std::shared_ptr<Texture> m_Texture;
    int Rank = 0;
    double time = 0;
};