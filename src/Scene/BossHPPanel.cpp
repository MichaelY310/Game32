#include "BossHPPanel.h"
#include "Render/Renderer.h"

BossHPPanel::BossHPPanel(std::shared_ptr<Entity> linkedEntity)
    : m_LinkedEntity(linkedEntity)
{

}

void BossHPPanel::Display(double HP)
{
    double maxHP = 100;
    Renderer::DrawRing(m_LinkedEntity->m_Position, 0.3, { 0.6, 0.3, 0.3 }, 0.5, -100, (maxHP - HP) / maxHP * 360 - 90);
}   