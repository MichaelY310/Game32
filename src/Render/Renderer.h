#pragma once

#include "DataTypes.h"
#include "Texture.h"

class Renderer
{
public:
    static void Init();
    static void Flush();
    static void DrawQuad(vec2 position, double scale, vec3 color, double alpha = 1.0, double depth = 0.0);
    static void DrawQuad(vec2 position, double scale, std::shared_ptr<Texture> texture, double depth = 0.0);
    static void DrawRing(vec2 position, double scale, vec3 color, double alpha = 1.0, double depth = 0.0, double angle = 360.0);

};