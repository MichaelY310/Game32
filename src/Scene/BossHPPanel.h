#pragma once
#include "Entity.h"
#include <memory>

class BossHPPanel
{
public:
    BossHPPanel(std::shared_ptr<Entity> linkedEntity);

    void Display();

    std::shared_ptr<Entity> m_LinkedEntity;

};