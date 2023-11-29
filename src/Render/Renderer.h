#pragma once

#include "DataTypes.h"
#include "Texture.h"

class Renderer
{
public:
    static void Init();
    static void Flush();
    static void DrawQuad(vec2 position, double scale, vec3 color);
    static void DrawQuad(vec2 position, double scale, std::shared_ptr<Texture> texture);

};