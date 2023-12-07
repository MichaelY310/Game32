#pragma once

#include "DataTypes.h"
#include "Render/Texture.h"
#include "Scene/Entity.h"

class Renderer
{
public:
    static void Init();
    static void Flush();
    static void DrawQuad(std::shared_ptr<Entity> entity);
    static void DrawQuad(std::Message, vec2 position, vec2 scale, vec3 color, double alpha = 1.0, double depth = 0.0);
    static void DrawQuad(std::Message, vec2 position, vec2 scale, std::shared_ptr<Texture> texture, double depth = 0.0);
    static void DrawRing(vec2 position, vec2 scale, vec3 color, double alpha = 1.0, double depth = 0.0, double angle = 360);
    static void DrawLeaderBoard(vec2 position, std::string Message);
};