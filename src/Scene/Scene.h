#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "Render/Texture.h"

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void OnUpdate(double timestep);
    void OnDisplay();


    std::vector<std::shared_ptr<Entity>> m_EntityList;
    double playerSpeed = 1.5;

    std::shared_ptr<Texture> texture;

};