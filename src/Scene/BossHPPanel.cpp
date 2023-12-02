#include "BossHPPanel.h"
#include "Render/Renderer.h"

BossHPPanel::BossHPPanel(std::shared_ptr<Entity> linkedEntity)
    : m_LinkedEntity(linkedEntity)
{

}

void BossHPPanel::Display()
{
    Renderer::DrawRing({0.0, 0.0}, 0.5, { 1.0, 1.0, 1.0 }, 1.0);
}   