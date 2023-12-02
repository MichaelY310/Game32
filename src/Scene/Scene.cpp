#include "Scene.h"

#include "Render/Renderer.h"
#include "Core/Input.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>

Scene::Scene()
{
    texture = Texture::Create("/mnt/c/Users/86166/Desktop/cs32/Game32/src/Asset/wall.jpg");
}

void Scene::OnUpdate(double timestep)
{
    if (m_CurrentStage == SceneStage::TITLE)
    { Scene::OnUpdateTitle(timestep); }
    else if (m_CurrentStage == SceneStage::CHOOSE_CHARACTER)
    { Scene::OnUpdateChooseCharacter(timestep); }
    else if (m_CurrentStage == SceneStage::CONVERSATION1)
    { Scene::OnUpdateConversation1(timestep); }
    else if (m_CurrentStage == SceneStage::BOSSFIGHT1)
    { Scene::OnUpdateBossfight1(timestep); }
}


void Scene::OnDisplay() 
{
    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Draw Player
    for (int i=0; i<m_EntityList.size(); i++)
    {
        std::shared_ptr<Entity> entity = m_EntityList[i];
        Renderer::DrawQuad(entity->m_Position, entity->m_Size, texture);
    }
    Renderer::Flush();
}

bool menuRemove = false;
bool stage = false;

void Scene::OnUpdateTitle(double timestep)
{
    std::cout << "running" << std::endl;
    if (m_CurrentStageTime == 0 && stage == false) {
        // std::cout << "yes" <<std::endl;
        m_Player = std::make_shared<Entity>(vec2(0.0, 0.0), 0.0f, 0.5f, EntityType::MENU);
        m_EntityList.push_back(m_Player);

        m_CurrentStageTime += timestep;
        stage = true;
    }
    
    if (Input::isKeyPressed('w'))
    {
        m_CurrentStage = SceneStage::CHOOSE_CHARACTER;
        m_CurrentStageTime = 0;
    }
    else if (Input::isKeyPressed('q')) {
        exit(1);
    }
}

// Player Created
void Scene::OnUpdateChooseCharacter(double timestep)
{
    if (menuRemove == false){
      
        m_EntityList.erase(m_EntityList.begin() + m_EntityList.size()-1);
        menuRemove = true;
    }
    m_CurrentStage = SceneStage::CONVERSATION1;
    m_Player = std::make_shared<Entity>(vec2(0.0, 0.0), 0.0f, 0.04f, EntityType::PLAYER);
    m_EntityList.push_back(m_Player);
    m_CurrentStageTime = 0;
}

void Scene::OnUpdateConversation1(double timestep)
{
    // Boss1 Move in
    if (m_CurrentStageTime == 0)
    {
        m_Boss1 = std::make_shared<Entity>(vec2(2.0, 1.0), 0.0f, 0.1f, EntityType::BOSS);
        m_EntityList.push_back(m_Boss1);
    }

    vec2 a = vec2(0.0, 0.5);
    if (m_Boss1->m_Position.x > a.x && m_Boss1->m_Position.y > a.y)
    {
        m_Boss1->m_Position = m_Boss1->m_Position + (vec2(0.0, 0.5) - vec2(2.0, 1.0)) * 0.01;
        m_CurrentStageTime += timestep;
    }
    else
    {
        m_CurrentStage = SceneStage::BOSSFIGHT1;
        m_CurrentStageTime = 0;
    }
}

void Scene::OnUpdateBossfight1(double timestep)
{
    std::shared_ptr<Entity> playerEntity;
    std::shared_ptr<Entity> bossEntity;

    std::vector<int> removeIndexList;
    for (int i = 0; i < m_EntityList.size(); i++)
    {
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // Player Move
        if (entity->m_EntityType == EntityType::PLAYER)
        {
            playerEntity = entity;
            PlayerMove(playerEntity, timestep);
        }
        // Player Bullet Move
        else if (entity->m_EntityType == EntityType::PLAYER_BULLET)
        {
            PlayerBulletMove(entity, timestep);
        }
        // Boss Move
        else if (entity->m_EntityType == EntityType::BOSS)
        {
            bossEntity = entity;
            Boss1Move(entity, timestep);
        }
        // Boss Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_BULLET)
        {
            Boss1BulletMove(entity, timestep);
        }

        // Delete Entity
        if (entity->m_Position.x > 2.0f || entity->m_Position.x < -2.0f || entity->m_Position.y > 1.1f || entity->m_Position.y < -1.1f)
        {
            removeIndexList.push_back(i);
        }
    }
    // PlayerShoot Bullet
    Scene::PlayerShootBullet(playerEntity, timestep);
    if (bossEntity) { Scene::Boss1ShootBullet(bossEntity, timestep); }

    // Delete Entity
    for (int i = 0; i < removeIndexList.size(); i++)
    {
        m_EntityList.erase(m_EntityList.begin() + removeIndexList[i] - i);
    }

    m_CurrentStageTime += timestep;

    // std::cout << m_EntityList.size() << std::endl;

    // m_CurrentStageTime = 0;

}


void Scene::PlayerMove(std::shared_ptr<Entity> playerEntity, double timestep)
{
    if (Input::isKeyPressed('z')) { 
        playerSpeed = 0.75; 
    }
    else { playerSpeed = 1.5; }

    if (Input::isKeyPressed(GLUT_KEY_UP) && Input::isKeyPressed(GLUT_KEY_LEFT))
    {
        if (playerEntity->m_Position.y < 1.0) { playerEntity->m_Position.y += timestep * playerSpeed; }
        if (playerEntity->m_Position.x > -1.9) { playerEntity->m_Position.x -= timestep * playerSpeed; }
    }
    else if (Input::isKeyPressed(GLUT_KEY_DOWN) && Input::isKeyPressed(GLUT_KEY_LEFT))
    {
        if (playerEntity->m_Position.y > -1.00) { playerEntity->m_Position.y -= timestep * playerSpeed; }
        if (playerEntity->m_Position.x > -1.9) { playerEntity->m_Position.x -= timestep * playerSpeed; }
    }
    else if (Input::isKeyPressed(GLUT_KEY_UP) && Input::isKeyPressed(GLUT_KEY_RIGHT))
    {
        if (playerEntity->m_Position.y > -1.00) { playerEntity->m_Position.y -= timestep * playerSpeed; }
        if (playerEntity->m_Position.x < 1.9) { playerEntity->m_Position.x += timestep * playerSpeed; }
    }
    else if (Input::isKeyPressed(GLUT_KEY_DOWN) && Input::isKeyPressed(GLUT_KEY_RIGHT))
    {
        if (playerEntity->m_Position.y > -1.00) { playerEntity->m_Position.y -= timestep * playerSpeed; }
        if (playerEntity->m_Position.x < 1.9) { playerEntity->m_Position.x += timestep * playerSpeed; }
    }
    else if (Input::isKeyPressed(GLUT_KEY_UP))
    {
        if (playerEntity->m_Position.y < 1.0) { playerEntity->m_Position.y += timestep * playerSpeed; }
    }
    else if (Input::isKeyPressed(GLUT_KEY_DOWN))
    {
        if (playerEntity->m_Position.y > -1.00) { playerEntity->m_Position.y -= timestep * playerSpeed; }
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


void Scene::PlayerShootBullet(std::shared_ptr<Entity> playerEntity, double timestep)
{
    currentBulletTime += timestep;
    if (Input::isKeyPressed(32))
    {
        if (prevBulletTime == 0 || currentBulletTime - prevBulletTime >= 0.3)
        {
            int bulletCount = 4;
            for (int i = 0; i < bulletCount; i++)
            {
                vec2 pos = playerEntity->m_Position;

                double xOffset = (double)i-((double)bulletCount - 1)/2;
                pos = pos + vec2(xOffset * playerSpeed * 0.05, 0.05);
                std::shared_ptr<Entity> playerBullet = std::make_shared<Entity>(pos, 90.0f, 0.03f, EntityType::PLAYER_BULLET);
                m_EntityList.push_back(playerBullet);
            }
            prevBulletTime = currentBulletTime;
        }
    }
}


void Scene::PlayerBulletMove(std::shared_ptr<Entity> playerBulletEntity, double timestep)
{
    float angleRadians = playerBulletEntity->m_Angle * (M_PI / 180.0);

    playerBulletEntity->m_Position.x += 2 * std::cos(angleRadians) * timestep;
    playerBulletEntity->m_Position.y += 2 * std::sin(angleRadians) * timestep;
}


void Scene::Boss1Move(std::shared_ptr<Entity> bossEntity, double timestep)
{
    if (Boss1Wait <= 0)
    {
        float angleRadians = bossEntity->m_Angle * (M_PI / 180.0);
        bossEntity->m_Position.x += 1 * std::cos(angleRadians) * timestep;
        bossEntity->m_Position.y += 1 * std::sin(angleRadians) * timestep;

        if (bossEntity->m_Position.x >= 1.0)
        {
            bossEntity->m_Angle = 180;
            Boss1Wait = 2;
        }
        else if (bossEntity->m_Position.x <= -1.0)
        {
            bossEntity->m_Angle = 0;
            Boss1Wait = 2;
        }
    }
    else 
    {
        Boss1Wait -= timestep;
    }

    // std::cout << Boss1Wait << std::endl;
}


void Scene::Boss1ShootBullet(std::shared_ptr<Entity> boss1Entity, double timestep)
{
    Boss1currentBigBulletTime += timestep;
    if (Boss1Wait > 0 && (Boss1prevBigBulletTime == 0 || Boss1currentBigBulletTime - Boss1prevBigBulletTime >= 0.5))
    {
        int bulletCount = 9;
        for (int i = 0; i < bulletCount; i++)
        {
            std::shared_ptr<Entity> boss1BigBullet = std::make_shared<Entity>(boss1Entity->m_Position, ((double)i * 360.0f / (double)bulletCount) + Boss1currentBigBulletTime * 100000, 0.08f, EntityType::BOSS_BULLET);
            m_EntityList.push_back(boss1BigBullet);
        }
        Boss1prevBigBulletTime = Boss1currentBigBulletTime;
    }
}

void Scene::Boss1BulletMove(std::shared_ptr<Entity> boss1BulletEntity, double timestep)
{
    float angleRadians = boss1BulletEntity->m_Angle * (M_PI / 180.0);

    boss1BulletEntity->m_Position.x += 2 * std::cos(angleRadians) * timestep;
    boss1BulletEntity->m_Position.y += 2 * std::sin(angleRadians) * timestep;
}