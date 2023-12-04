#pragma once
#include "Entity.h"
#include <memory>

class BossHPPanel
{
public:
    BossHPPanel(std::shared_ptr<Entity> linkedEntity);

    void Display(double HP);

    std::shared_ptr<Entity> m_LinkedEntity;

};