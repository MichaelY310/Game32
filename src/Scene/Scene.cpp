#include "Scene.h"

#include "Render/Renderer.h"
#include "Core/Input.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>

Scene::Scene()
{
    texture = Texture::Create("/mnt/c/Users/86166/Desktop/cs32/Game32/src/Asset/wall.jpg");
    std::shared_ptr<Entity> player = std::make_shared<Entity>(vec2(0.0, 0.0), 0.0f, 0.04f, EntityType::PLAYER);
    m_EntityList.push_back(player);

}

void Scene::OnUpdate(double timestep)
{
    std::shared_ptr<Entity> playerEntity;

    int i = 0;
    while (i < m_EntityList.size())
    {
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // Player
        if (entity->m_EntityType == EntityType::PLAYER)
        {
            if (Input::isKeyPressed('z')) { 
                playerSpeed = 0.75; 
            }
            else { playerSpeed = 1.5; }

            playerEntity = entity;
            if (Input::isKeyPressed(GLUT_KEY_UP) && Input::isKeyPressed(GLUT_KEY_LEFT))
            {
                if (playerEntity->m_Position.y < 0.95) { playerEntity->m_Position.y += timestep * playerSpeed; }
                if (playerEntity->m_Position.x > -1.9) { playerEntity->m_Position.x -= timestep * playerSpeed; }
            }
            else if (Input::isKeyPressed(GLUT_KEY_DOWN) && Input::isKeyPressed(GLUT_KEY_LEFT))
            {
                if (playerEntity->m_Position.y > -1.05) { playerEntity->m_Position.y -= timestep * playerSpeed; }
                if (playerEntity->m_Position.x > -1.9) { playerEntity->m_Position.x -= timestep * playerSpeed; }
            }
            else if (Input::isKeyPressed(GLUT_KEY_UP) && Input::isKeyPressed(GLUT_KEY_RIGHT))
            {
                if (playerEntity->m_Position.y > -1.05) { playerEntity->m_Position.y -= timestep * playerSpeed; }
                if (playerEntity->m_Position.x < 1.9) { playerEntity->m_Position.x += timestep * playerSpeed; }
            }
            else if (Input::isKeyPressed(GLUT_KEY_DOWN) && Input::isKeyPressed(GLUT_KEY_RIGHT))
            {
                if (playerEntity->m_Position.y > -1.05) { playerEntity->m_Position.y -= timestep * playerSpeed; }
                if (playerEntity->m_Position.x < 1.9) { playerEntity->m_Position.x += timestep * playerSpeed; }
            }
            else if (Input::isKeyPressed(GLUT_KEY_UP))
            {
                if (playerEntity->m_Position.y < 0.95) { playerEntity->m_Position.y += timestep * playerSpeed; }
            }
            else if (Input::isKeyPressed(GLUT_KEY_DOWN))
            {
                if (playerEntity->m_Position.y > -1.05) { playerEntity->m_Position.y -= timestep * playerSpeed; }
            }            
            else if (Input::isKeyPressed(GLUT_KEY_LEFT))
            {
                if (playerEntity->m_Position.x > -1.9) { playerEntity->m_Position.x -= timestep * playerSpeed; }
            }            
            else if (Input::isKeyPressed(GLUT_KEY_RIGHT))
            {
                if (playerEntity->m_Position.x < 1.9) { playerEntity->m_Position.x += timestep * playerSpeed; }
            }
        }

        // Player Bullet
        if (entity->m_EntityType == EntityType::PLAYER_BULLET)
        {
            float angleRadians = entity->m_Angle * (M_PI / 180.0);

            entity->m_Position.x += 1 * std::cos(angleRadians) * timestep;
            entity->m_Position.y += 1 * std::sin(angleRadians) * timestep;
        }

        if (entity->m_Position.x > 2.0f || entity->m_Position.x < -2.0f || entity->m_Position.y > 1.1f || entity->m_Position.y < -1.1f)
        {
            m_EntityList.erase(m_EntityList.begin() + i);
        }
        else
        {
            i++;
        }
    }

    if (Input::isKeyPressed(32))
    {
        for (int i = 0; i < 4; i++)
        {
            vec2 pos = playerEntity->m_Position;
            pos = pos + vec2((i-1.5) * playerSpeed * 0.05, 0.05);
            std::shared_ptr<Entity> playerBullet = std::make_shared<Entity>(pos, 90.0f, 0.03f, EntityType::PLAYER_BULLET);
            m_EntityList.push_back(playerBullet);
        }
    }

    std::cout << m_EntityList.size() << std::endl;


}


void Scene::OnDisplay() 
{
    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    for (int i=0; i<m_EntityList.size(); i++)
    {
        std::shared_ptr<Entity> entity = m_EntityList[i];
        if (Input::isKeyPressed('a')) { std::cout << entity->m_Position.x << " " << entity->m_Position.y << " " << playerSpeed << std::endl; }
        // Renderer::DrawQuad(entity->m_Position, entity->m_Size, { 0.2, 0.3, 0.4 });
        // std::cout << texture->m_RendererID << std::endl;
        Renderer::DrawQuad(entity->m_Position, entity->m_Size, texture);
    }
    Renderer::Flush();

}