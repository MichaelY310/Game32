#include "Scene.h"

#include "Render/Renderer.h"
#include "Core/Input.h"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

double getRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    double randomValue = dis(gen);

    return randomValue;
}

Scene::Scene()
{
    Init();
}

void Scene::Init()
{
    startIcon = Texture::Create("Start.png");
    titleIcon = Texture::Create("Title.png");
    How_To_Play_Icon = Texture::Create("How_To_Play.png");
    exitIcon = Texture::Create("Exit.png");
    FailTexture = Texture::Create("Fail.png");
    SuccessIcon = Texture::Create("Success.png");

    PlayerNormal = Texture::Create("PlayerNormal0.png");
    PlayerNormalArray = { Texture::Create("PlayerNormal0.png"), Texture::Create("PlayerNormal1.png"), Texture::Create("PlayerNormal2.png"), Texture::Create("PlayerNormal3.png"), Texture::Create("PlayerNormal4.png"), Texture::Create("PlayerNormal5.png"), Texture::Create("PlayerNormal6.png"), Texture::Create("PlayerNormal7.png"), Texture::Create("PlayerNormal6.png"), Texture::Create("PlayerNormal5.png"), Texture::Create("PlayerNormal4.png"), Texture::Create("PlayerNormal3.png"), Texture::Create("PlayerNormal2.png"), Texture::Create("PlayerNormal1.png") };
    PlayerRight = Texture::Create("PlayerLeft0.png");
    PlayerLeftArray = { Texture::Create("PlayerLeft0.png"), Texture::Create("PlayerLeft1.png"), Texture::Create("PlayerLeft2.png"), Texture::Create("PlayerLeft3.png"), Texture::Create("PlayerLeft4.png"), Texture::Create("PlayerLeft5.png"), Texture::Create("PlayerLeft6.png"), Texture::Create("PlayerLeft7.png")};
    PlayerLeft = Texture::Create("PlayerRight0.png");
    PlayerRightArray = { Texture::Create("PlayerRight0.png"), Texture::Create("PlayerRight1.png"), Texture::Create("PlayerRight2.png"), Texture::Create("PlayerRight3.png"), Texture::Create("PlayerRight4.png"), Texture::Create("PlayerRight5.png"), Texture::Create("PlayerRight6.png"), Texture::Create("PlayerRight7.png")};

    Boss1Texture = Texture::Create("Boss1.png");
    Boss2Texture = Texture::Create("Boss2.png");
    Boss3Texture = Texture::Create("Boss3.png");

    BossBigBulletTexture = Texture::Create("BossBigBullet.png");
    BossSmallBulletTexture = Texture::Create("BossSmallBullet.png");
    PlayerBulletTexture = Texture::Create("PlayerBullet2.png");


    PlayerLivesTexture = Texture::Create("PlayerLives.png");
    HowToPlayTexture = Texture::Create("How To Play.png");
}

void Scene::OnUpdate(double timestep)
{
    // Scene::OnUpdateTest(timestep); 
    // return;

    if (startIcon->m_RendererID == 0) { Init(); }

    if (m_CurrentStage == SceneStage::TITLE)
    { Scene::OnUpdateTitle(timestep); TimeUsed = 0;}
    else if (m_CurrentStage == SceneStage::CHOOSE_CHARACTER)
    { Scene::OnUpdateChooseCharacter(timestep); }

    else if (m_CurrentStage == SceneStage::CONVERSATION1)
    { Scene::OnUpdateConversation1(timestep);}
    else if (m_CurrentStage == SceneStage::BOSSFIGHT1)
    { Scene::OnUpdateBossfight1(timestep); TimeUsed += timestep;}

    else if (m_CurrentStage == SceneStage::CONVERSATION2)
    { Scene::OnUpdateConversation2(timestep); }
    else if (m_CurrentStage == SceneStage::BOSSFIGHT2)
    { Scene::OnUpdateBossfight2(timestep); TimeUsed += timestep;}

    else if (m_CurrentStage == SceneStage::CONVERSATION3)
    { Scene::OnUpdateConversation3(timestep); }
    else if (m_CurrentStage == SceneStage::BOSSFIGHT3)
    { Scene::OnUpdateBossfight3(timestep); TimeUsed += timestep;}

    else if (m_CurrentStage == SceneStage::LEADERBOARD)
    {Scene::OnUpdateLeaderBoard(timestep);}

    else if (m_CurrentStage == SceneStage::SUCCEED)
    {Scene::OnUpdateSucceed(timestep);}


    else if (m_CurrentStage == SceneStage::FAILED)
    { Scene::OnUpdateFailed(timestep); }
}


void Scene::OnDisplay() 
{
    Renderer::Init();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Player lives
    if (m_CurrentStage == SceneStage::BOSSFIGHT1 || m_CurrentStage == SceneStage::BOSSFIGHT2 || m_CurrentStage == SceneStage::BOSSFIGHT3)
    {
        for (int i=0; i<playerLives; i++)
        {
            Renderer::DrawQuad(vec2(1.85 - 0.13 * i, 0.9), vec2(0.1, 0.1), vec3(1.0, 0.0, 0.0), PlayerLivesTexture, 1.0, 114.0);
        }
    }

    if (m_CurrentStage == SceneStage::BOSSFIGHT1 || m_CurrentStage == SceneStage::BOSSFIGHT2 || m_CurrentStage == SceneStage::BOSSFIGHT3 || m_CurrentStage == SceneStage::CONVERSATION1 || m_CurrentStage == SceneStage::CONVERSATION2 || m_CurrentStage == SceneStage::CONVERSATION3)
    {
        std::string Message =  "Time: ";
        Message += std::to_string(TimeUsed);
        Renderer::DrawLeader(vec2(-1.85, 0.9), Message);
    }

    if (m_CurrentStage == SceneStage::LEADERBOARD)
    {
        double PosY = 0.0;
        int R = 1;

        for (int i=0; i < Leaders.size(); i++) 
        {
            std::string Message =  "Top ";
            Message += std::to_string(R);
            Message +=  " : ";
            Message += std::to_string(TimeUsed);
            Renderer::DrawLeader(vec2(-0.3, PosY), Message);
            
            PosY -= 0.2;
            R += 1;
        }
    }

    if (BlackCoverTime > 0)
    {
        double transition = 20;
        if (BlackCoverTime >= MaxBlackCoverTime - transition) { Renderer::DrawQuad(vec2(0, 0), vec2(4.0, 4.0), vec3(0.0, 0.0, 0.0), (MaxBlackCoverTime - BlackCoverTime) / transition, 10000); }
        else if (BlackCoverTime <= 20) { Renderer::DrawQuad(vec2(0, 0), vec2(4.0, 4.0), vec3(0.0, 0.0, 0.0), BlackCoverTime / transition, 10000); }
        else { Renderer::DrawQuad(vec2(0, 0), vec2(4.0, 4.0), vec3(0.0, 0.0, 0.0), 1.0, 10000); }
        BlackCoverTime -= 1;
    }

    if (flashUnit > 0) { flashUnit -= 1; }

    if (Boss1HPPanel) { Boss1HPPanel->Display(Boss1HP); }
    if (Boss2HPPanel) { Boss2HPPanel->Display(Boss2HP); }
    if (Boss3HPPanel) { Boss3HPPanel->Display(Boss3HP); }


    // Draw
    for (int i=0; i<m_EntityList.size(); i++)
    {
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // player flash
        if (entity->m_EntityType == EntityType::PLAYER && playerLives > 0) {
            if (flashUnit % 10 == 0)
            {
                entity->m_Alpha = 1.0f;
            }
            else {
                entity->m_Alpha = 0.0f;
            }
        }
        Renderer::DrawQuad(entity);
    }

    Renderer::Flush();
}



void Scene::OnUpdateTitle(double timestep)
{

    if (m_CurrentStageTime == 0)
    {
        m_Choice = 0;
        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

        std::shared_ptr<Entity> menu1 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.6), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, startIcon);
        m_EntityList.push_back(menu1);

        std::shared_ptr<Entity> menu2 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.0), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, How_To_Play_Icon);
        m_EntityList.push_back(menu2);

        std::shared_ptr<Entity> menu3 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, -0.6), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, exitIcon);
        m_EntityList.push_back(menu3);

        std::shared_ptr<Entity> choice = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.4), 0.0f, vec2(1.0, 0.5), vec3(0.0, 0.0, 0.0), 1, -1);
        m_EntityList.push_back(choice);
    }

    if (m_Choice == 0)
    {
        m_EntityList[3]->m_Position = vec2(0.0, 0.6);
    }
    else if (m_Choice == 1)
    {
        m_EntityList[3]->m_Position = vec2(0.0, 0.0);
    }
    else
    {
        m_EntityList[3]->m_Position = vec2(0.0, -0.6);
    }

    if (Input::isKeyPressed(GLUT_KEY_UP))
    {
        if (m_Choice != 0 && lastClick < 0)
        {
            lastClick = 0.3;
            m_Choice -= 1;
        }
    }
    if (Input::isKeyPressed(GLUT_KEY_DOWN))
    {
        if (m_Choice != 2 && lastClick < 0)
        {
            lastClick = 0.3;
            m_Choice += 1;
        }
    }  

    if (lastClick >= 0) { lastClick -= timestep; }
    if (lastSpacePress >= 0) { lastSpacePress -= timestep; }

    if (IsDisplayHowToPlay) {
        if (tempFollow == 0)
        {
            tempFollow = 1;
            std::shared_ptr<Entity> HowToPlay = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.0), 0.0f, vec2(2.5, 2), vec3(1.0, 1.0, 1.0), 1, 10, HowToPlayTexture);
            m_EntityList.push_back(HowToPlay);
        }

        if (Input::isKeyPressed(32) && lastSpacePress < 0)
        {
            IsDisplayHowToPlay = false;
            lastSpacePress = 0.3;
            m_EntityList.erase(m_EntityList.end() - 1, m_EntityList.end());
        }
        m_CurrentStageTime += timestep;
        return;
    }


    if (Input::isKeyPressed(32) && lastSpacePress < 0)
    {
        lastSpacePress = 0.3;
        if (m_Choice == 0)
        {
            m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

            Boss1HP = 100;
            Boss1MaxMode = 3;
            Boss1Mode = 0;
            Boss1Wait = 0;  // Wait 
            Boss1prevBigBulletTime = 0;
            Boss1currentBigBulletTime = 0;
            BOSS1DEAD = false;

            Boss2HP = 100;
            Boss2MaxMode = 3;
            Boss2Mode = 0;
            Boss2Wait = 0;  // Wait 
            Boss2prevBigBulletTime = 0;
            Boss2currentBigBulletTime = 0;
            BOSS2DEAD = false;

            Boss3HP = 100;
            Boss3MaxMode = 3;
            Boss3Mode = 0;
            Boss3MoveTime = 0;
            Boss3ShootTime = 0;
            Boss3WaitTime = 0;  // Wait 

            Boss3prevBigBulletTime = 0;
            Boss3currentBigBulletTime = 0;

            PLAYERDEAD = false;
            playerLives = 2;
            playerSpeed = 1.5;
            prevBulletTime = 0;
            currentBulletTime = 0;
            flashUnit = 0;

            BlackCoverTime = 0;
            MaxBlackCoverTime = 400;

            m_CurrentStage = SceneStage::CHOOSE_CHARACTER;
            m_CurrentStageTime = 0;
            return;
        }
        else if (m_Choice == 1)
        {
            IsDisplayHowToPlay = true;
            tempFollow = 0;
        }
        else {
            
            exit(0);
        }
    }
    m_CurrentStageTime += timestep;
}

void Scene::OnUpdateChooseCharacter(double timestep)
{
    m_CurrentStage = SceneStage::CONVERSATION1;
    m_CurrentStageTime = 0;
}

void Scene::OnUpdateConversation1(double timestep)
{
    // Boss1 Move in
    if (m_CurrentStageTime == 0)
    {
        playerLives += 1;
        BlackCoverTime = MaxBlackCoverTime;
        std::shared_ptr<Entity> player = std::make_shared<Entity>(EntityType::PLAYER, vec2(0.0, -0.5), 0.0f, vec2(PLAYER_SIZE * 2, PLAYER_SIZE * 2), vec3(1.0, 1.0, 1.0), 1.0, 100.0, PlayerNormal);
        m_EntityList.push_back(player);

        m_Boss1 = std::make_shared<Entity>(EntityType::BOSS, vec2(2.0, 1.0), 0.0f, vec2(BOSS_SIZE * 2, BOSS_SIZE * 2 * 2), vec3(vec3(1.0, 1.0, 1.0)), 1.0, 90.0, Boss1Texture);
        m_EntityList.push_back(m_Boss1);
    }

    if (BlackCoverTime > 0)
    {
        m_CurrentStageTime += timestep;
        return;
    }

    vec2 a = vec2(0.0, 0.5);
    if (m_Boss1->m_Position.x > a.x && m_Boss1->m_Position.y > a.y)
    {
        m_Boss1->m_Position = m_Boss1->m_Position + (vec2(0.0, 0.5) - vec2(2.0, 1.0)) * 1 * timestep;
        m_CurrentStageTime += timestep;
    }
    else
    {
        m_CurrentStage = SceneStage::BOSSFIGHT1;
        m_CurrentStageTime = 0;
        return;
    }
}

void Scene::OnUpdateBossfight1(double timestep)
{
    if (m_CurrentStageTime == 0)
    {
        Boss1HPPanel = std::make_shared<BossHPPanel>(m_Boss1);
    }

    std::shared_ptr<Entity> playerEntity;
    std::shared_ptr<Entity> bossEntity;

    std::vector<int> removeIndexList;
    for (int i = 0; i < m_EntityList.size(); i++)
    {
        bool deleted = false;
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // Player Move
        if (entity->m_EntityType == EntityType::PLAYER)
        {
            playerEntity = entity;

            // Stop moving if Boss or Player is dead
            if (playerLives > 0)
            {
                if (Boss1HP > 0) {
                    PlayerMove(playerEntity, timestep);
                }
            }
            else {
                PlayerDie(playerEntity, timestep);
                if (PLAYERDEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Player Bullet Move
        else if (entity->m_EntityType == EntityType::PLAYER_BULLET)
        {
            // Cause damage if the Boss is not dead
            if (Boss1HP > 0 && bossEntity->m_Position.DistanceTo(entity->m_Position) < PLAYER_BULLET_RADIUS + BOSS_RADIUS)
            {
                Boss1HP -= playerATK;
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            PlayerBulletMove(entity, timestep);
        }
        // Boss Move
        else if (entity->m_EntityType == EntityType::BOSS)
        {
            bossEntity = entity;
            if (Boss1HP > 0) {
                Boss1Move(entity, timestep);
            } 
            else {
                Boss1Die(entity, timestep);
                if (BOSS1DEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Boss Big Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_BIG_BULLET)
        {
            // Delete if Boss is dead
            if (Boss1HP <= 0) {
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            else 
            {
                // Cause damage if player is alive
                if (playerEntity) {
                    if (playerEntity->m_Position.DistanceTo(entity->m_Position) < BOSS_BIG_BULLET_RADIUS + PLAYER_RADIUS)
                    {
                        // Ineffective time out     the last one should not flash
                        if (flashUnit == 0)
                        {
                            playerLives -= 1;
                            if (playerLives > 0) { flashUnit = 100; } 

                            if (!deleted)
                            {
                                removeIndexList.push_back(i);
                                deleted = true;
                            }
                        }
                    }
                }
                Boss1BulletMove(entity, timestep);
            }
        }

        // Delete Entity
        if (entity->m_Position.x > 2.0f || entity->m_Position.x < -2.0f || entity->m_Position.y > 1.1f || entity->m_Position.y < -1.1f)
        {
            if (!deleted)
            {
                removeIndexList.push_back(i);
                deleted = true;
            }
        }
    }

    // Add Bullet
    if (playerEntity) {
        if (playerLives > 0) { Scene::PlayerShootBullet(playerEntity, timestep); }
    }
    if (bossEntity) { 
        if (Boss1HP > 0) { Scene::Boss1ShootBullet(bossEntity, timestep); }
    }

    // Delete Entity
    for (int i = 0; i < removeIndexList.size(); i++)
    {
        m_EntityList.erase(m_EntityList.begin() + removeIndexList[i] - i);
    }

    m_CurrentStageTime += timestep;

    if (BOSS1DEAD)
    {
        Boss1HPPanel = nullptr;
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::CONVERSATION2;
        return;
    }
    else if (PLAYERDEAD)
    {
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::FAILED;
        return;
    }
}

void Scene::OnUpdateConversation2(double timestep)
{
    // Boss2 Move in
    if (m_CurrentStageTime == 0)
    {
        playerLives++;
        
        BlackCoverTime = MaxBlackCoverTime;
        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

        std::shared_ptr<Entity> player = std::make_shared<Entity>(EntityType::PLAYER, vec2(0.0, -0.5), 0.0f, vec2(PLAYER_SIZE * 2, PLAYER_SIZE * 2), vec3(1.0, 1.0, 1.0), 1.0, 100.0, PlayerNormal);
        m_EntityList.push_back(player);
        m_Boss2 = std::make_shared<Entity>(EntityType::BOSS, vec2(2.0, 1.0), 0.0f, vec2(BOSS_SIZE * 2, BOSS_SIZE * 2 * 2), vec3(1.0, 1.0, 1.0), 1.0, 90.0, Boss2Texture);
        m_EntityList.push_back(m_Boss2);
    }

    if (BlackCoverTime > 0)
    {
        m_CurrentStageTime += timestep;
        return;
    }

    vec2 a = vec2(0.0, 0.5);
    if (m_Boss2->m_Position.x > a.x && m_Boss2->m_Position.y > a.y)
    {
        m_Boss2->m_Position = m_Boss2->m_Position + (vec2(0.0, 0.5) - vec2(2.0, 1.0)) * 1 * timestep;
        m_CurrentStageTime += timestep;
    }
    else
    {
        m_CurrentStage = SceneStage::BOSSFIGHT2;
        m_CurrentStageTime = 0;
        return;
    }
}

void Scene::OnUpdateBossfight2(double timestep)
{
    if (m_CurrentStageTime == 0)
    {
        Boss2HPPanel = std::make_shared<BossHPPanel>(m_Boss2);
    }

    std::shared_ptr<Entity> playerEntity;
    std::shared_ptr<Entity> bossEntity;

    std::vector<int> removeIndexList;
    for (int i = 0; i < m_EntityList.size(); i++)
    {
        bool deleted = false;
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // Player Move
        if (entity->m_EntityType == EntityType::PLAYER)
        {
            playerEntity = entity;

            // Stop moving if Boss or Player is dead
            if (playerLives > 0)
            {
                if (Boss2HP > 0) {
                    PlayerMove(playerEntity, timestep);
                }
            }
            else {
                PlayerDie(playerEntity, timestep);
                if (PLAYERDEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Player Bullet Move
        else if (entity->m_EntityType == EntityType::PLAYER_BULLET)
        {
            // Cause damage if the Boss is not dead
            if (Boss2HP > 0 && bossEntity->m_Position.DistanceTo(entity->m_Position) < PLAYER_BULLET_RADIUS + BOSS_RADIUS)
            {
                Boss2HP -= playerATK;
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            PlayerBulletMove(entity, timestep);
        }
        // Boss Move
        else if (entity->m_EntityType == EntityType::BOSS)
        {
            bossEntity = entity;
            if (Boss2HP > 0) {
                Boss2Move(entity, timestep);
            } 
            else {
                Boss2Die(entity, timestep);
                if (BOSS2DEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Boss Big Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_BIG_BULLET)
        {
            // Delete if Boss is dead
            if (Boss2HP <= 0) {
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            else 
            {
                // Cause damage if player is alive
                if (playerEntity) {
                    if (playerEntity->m_Position.DistanceTo(entity->m_Position) < BOSS_BIG_BULLET_RADIUS + PLAYER_RADIUS)
                    {
                        // Ineffective time out     the last one should not flash
                        if (flashUnit == 0)
                        {
                            playerLives -= 1;
                            if (playerLives > 1) { flashUnit = 100; } 

                            if (!deleted)
                            {
                                removeIndexList.push_back(i);
                                deleted = true;
                            }
                        }
                    }
                }
                Boss2BulletMove(entity, timestep);
            }
        }

        // Boss Big Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_SMALL_BULLET)
        {
            // Delete if Boss is dead
            if (Boss2HP <= 0) {
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            else 
            {
                // Cause damage if player is alive
                if (playerEntity) {
                    if (playerEntity->m_Position.DistanceTo(entity->m_Position) < BOSS_SMALL_BULLET_RADIUS + PLAYER_RADIUS)
                    {
                        // Ineffective time out     the last one should not flash
                        if (flashUnit == 0)
                        {
                            playerLives -= 1;
                            if (playerLives > 1) { flashUnit = 100; } 

                            if (!deleted)
                            {
                                removeIndexList.push_back(i);
                                deleted = true;
                            }
                        }
                    }
                }
                Boss2BulletMove(entity, timestep);
            }
        }

        // Delete Entity
        if (entity->m_Position.x > 2.0f || entity->m_Position.x < -2.0f || entity->m_Position.y > 1.1f || entity->m_Position.y < -1.1f)
        {
            if (!deleted)
            {
                removeIndexList.push_back(i);
                deleted = true;
            }
        }
    }

    // Add Bullet
    if (playerEntity) {
        if (playerLives > 0) { Scene::PlayerShootBullet(playerEntity, timestep); }
    }
    if (bossEntity) { 
        if (Boss2HP > 0) { Scene::Boss2ShootBullet(bossEntity, timestep); }
    }

    // Delete Entity
    for (int i = 0; i < removeIndexList.size(); i++)
    {
        m_EntityList.erase(m_EntityList.begin() + removeIndexList[i] - i);
    }

    m_CurrentStageTime += timestep;

    if (BOSS2DEAD)
    {
        Boss2HPPanel = nullptr;
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::CONVERSATION3;
        return;
    }
    else if (PLAYERDEAD)
    {
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::FAILED;
        return;
    }
}

void Scene::OnUpdateConversation3(double timestep)
{
    // Boss2 Move in
    if (m_CurrentStageTime == 0)
    {
        playerLives++;
        
        BlackCoverTime = MaxBlackCoverTime;
        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

        std::shared_ptr<Entity> player = std::make_shared<Entity>(EntityType::PLAYER, vec2(0.0, -0.5), 0.0f, vec2(PLAYER_SIZE * 2, PLAYER_SIZE * 2), vec3(1.0, 1.0, 1.0), 1.0, 100.0, PlayerNormal);
        m_EntityList.push_back(player);
        m_Boss3 = std::make_shared<Entity>(EntityType::BOSS, vec2(2.0, 1.0), 0.0f, vec2(BOSS_SIZE * 2, BOSS_SIZE * 2 * 2), vec3(1.0, 1.0, 1.0), 1.0, 90.0, Boss3Texture);
        m_EntityList.push_back(m_Boss3);
    }

    if (BlackCoverTime > 0)
    {
        m_CurrentStageTime += timestep;
        return;
    }

    vec2 a = vec2(0.0, 0.7);
    if (m_Boss3->m_Position.x > a.x && m_Boss3->m_Position.y > a.y)
    {
        m_Boss3->m_Position = m_Boss3->m_Position + (vec2(0.0, 0.7) - vec2(2.0, 1.0)) * 1 * timestep;
        m_CurrentStageTime += timestep;
    }
    else
    {
        m_CurrentStage = SceneStage::BOSSFIGHT3;
        m_CurrentStageTime = 0;
        return;
    }
}

void Scene::OnUpdateBossfight3(double timestep)
{
    if (m_CurrentStageTime == 0)
    {
        Boss3HPPanel = std::make_shared<BossHPPanel>(m_Boss3);
    }

    std::shared_ptr<Entity> playerEntity;
    std::shared_ptr<Entity> bossEntity;

    std::vector<int> removeIndexList;
    for (int i = 0; i < m_EntityList.size(); i++)
    {
        bool deleted = false;
        std::shared_ptr<Entity> entity = m_EntityList[i];

        // Player Move
        if (entity->m_EntityType == EntityType::PLAYER)
        {
            playerEntity = entity;

            // Stop moving if Boss or Player is dead
            if (playerLives > 0)
            {
                if (Boss3HP > 0) {
                    PlayerMove(playerEntity, timestep);
                }
            }
            else {
                PlayerDie(playerEntity, timestep);
                if (PLAYERDEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Player Bullet Move
        else if (entity->m_EntityType == EntityType::PLAYER_BULLET)
        {
            // Cause damage if the Boss is not dead
            if (Boss3HP > 0 && bossEntity->m_Position.DistanceTo(entity->m_Position) < PLAYER_BULLET_RADIUS + BOSS_RADIUS)
            {
                Boss3HP -= playerATK;
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            PlayerBulletMove(entity, timestep);
        }
        // Boss Move
        else if (entity->m_EntityType == EntityType::BOSS)
        {
            bossEntity = entity;
            if (Boss3HP > 0) {
                Boss3Move(entity, playerEntity, timestep);
            } 
            else {
                Boss3Die(entity, timestep);
                if (BOSS3DEAD)
                {
                    if (!deleted)
                    {
                        removeIndexList.push_back(i);
                        deleted = true;
                    }
                }
            }
        }
        // Boss Big Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_BIG_BULLET)
        {
            // Delete if Boss is dead
            if (Boss3HP <= 0) {
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            else 
            {
                // Cause damage if player is alive
                if (playerEntity) {
                    if (playerEntity->m_Position.DistanceTo(entity->m_Position) < BOSS_BIG_BULLET_RADIUS + PLAYER_RADIUS)
                    {
                        // Ineffective time out     the last one should not flash
                        if (flashUnit == 0)
                        {
                            playerLives -= 1;
                            if (playerLives > 1) { flashUnit = 100; } 

                            if (!deleted)
                            {
                                removeIndexList.push_back(i);
                                deleted = true;
                            }
                        }
                    }
                }
                Boss3BulletMove(entity, timestep);
            }
        }

        // Boss Small Bullet Move
        else if (entity->m_EntityType == EntityType::BOSS_SMALL_BULLET)
        {
            // Delete if Boss is dead
            if (Boss3HP <= 0) {
                if (!deleted)
                {
                    removeIndexList.push_back(i);
                    deleted = true;
                }
            }
            else 
            {
                // Cause damage if player is alive
                if (playerEntity) {
                    if (playerEntity->m_Position.DistanceTo(entity->m_Position) < BOSS_SMALL_BULLET_RADIUS + PLAYER_RADIUS)
                    {
                        // Ineffective time out     the last one should not flash
                        if (flashUnit == 0)
                        {
                            playerLives -= 1;
                            if (playerLives > 1) { flashUnit = 100; } 

                            if (!deleted)
                            {
                                removeIndexList.push_back(i);
                                deleted = true;
                            }
                        }
                    }
                }
                Boss3BulletMove(entity, timestep);
            }
        }

        // Delete Entity
        if (entity->m_Position.x > 2.0f || entity->m_Position.x < -2.0f || entity->m_Position.y > 1.1f || entity->m_Position.y < -1.1f)
        {
            if (!deleted)
            {
                removeIndexList.push_back(i);
                deleted = true;
            }
        }
    }

    // Add Bullet
    if (playerEntity) {
        if (playerLives > 0) { Scene::PlayerShootBullet(playerEntity, timestep); }
    }
    if (bossEntity) { 
        if (Boss3HP > 0) { Scene::Boss3ShootBullet(bossEntity, timestep); }
    }

    // Delete Entity
    for (int i = 0; i < removeIndexList.size(); i++)
    {
        m_EntityList.erase(m_EntityList.begin() + removeIndexList[i] - i);
    }

    m_CurrentStageTime += timestep;

    if (BOSS3DEAD)
    {
        Boss3HPPanel = nullptr;
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::LEADERBOARD;
        return;
    }
    else if (PLAYERDEAD)
    {
        m_CurrentStageTime = 0;
        m_CurrentStage = SceneStage::FAILED;
        return;
    }
}


void Scene::OnUpdateLeaderBoard(double timestep)
{

    if (m_CurrentStageTime == 0)
    {
        m_Choice = 0;

        Leaders.push_back(TimeUsed);
        std::sort(Leaders.begin(), Leaders.end());

        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end()); 

        std::shared_ptr<Entity> SUCCESS = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.4), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, SuccessIcon);
        m_EntityList.push_back(SUCCESS);

        // std::shared_ptr<Entity> leaderBorad = std::make_shared<Entity>(EntityType::LEADERBOARD, vec2(-1.0, -0.4), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0);
        // m_EntityList.push_back(leaderBorad);

        // std::shared_ptr<Entity> choice = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.4), 0.0f, vec2(1.2, 0.5), vec3(0.0, 0.0, 0.0), 1, -1);
        // m_EntityList.push_back(choice);


        double PosY = 0.0;
        int R = 1;
    }

    if (m_Choice == 0)
    {
        m_EntityList[2]->m_Position = vec2(0.0, 0.4);
    }
    else
    {
        m_EntityList[2]->m_Position = vec2(0.0, -0.4);
    }

    if (Input::isKeyPressed(GLUT_KEY_UP))
    {
        m_Choice = 0;
    }    
    if (Input::isKeyPressed(GLUT_KEY_DOWN))
    {
        m_Choice = 1;
    }  

    if (Input::isKeyPressed(32))
    {
        lastSpacePress = 0.3;
        if (m_Choice == 0)
        {
            m_CurrentStage = SceneStage::SUCCEED;
            m_CurrentStageTime = 0;
            return;
        }
        else {
            exit(0);
        }
    }
    m_CurrentStageTime += timestep;
}


void Scene::OnUpdateSucceed(double timestep) // Success and restart the game  
{
    if (m_CurrentStageTime == 0)
    {
        m_Choice = 0;

        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

        std::shared_ptr<Entity> menu1 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.4), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, titleIcon);
        m_EntityList.push_back(menu1);

        std::shared_ptr<Entity> menu2 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, -0.4), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, exitIcon);
        m_EntityList.push_back(menu2);

        std::shared_ptr<Entity> choice = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.4), 0.0f, vec2(1.2, 0.5), vec3(0.0, 0.0, 0.0), 1, -1);
        m_EntityList.push_back(choice);
    }

    if (m_Choice == 0)
    {
        m_EntityList[2]->m_Position = vec2(0.0, 0.4);
    }
    else
    {
        m_EntityList[2]->m_Position = vec2(0.0, -0.4);
    }

    if (Input::isKeyPressed(GLUT_KEY_UP))
    {
        m_Choice = 0;
    }    
    if (Input::isKeyPressed(GLUT_KEY_DOWN))
    {
        m_Choice = 1;
    }  

    if (Input::isKeyPressed(32))
    {
        lastSpacePress = 0.3;
        if (m_Choice == 0)
        {
            m_CurrentStage = SceneStage::TITLE;
            m_CurrentStageTime = 0;
            return;
        }
        else {
            exit(0);
        }
    }
    m_CurrentStageTime += timestep;
}


void Scene::OnUpdateFailed(double timestep)
{
    if (m_CurrentStageTime == 0)
    {
        Boss1HPPanel = nullptr;
        Boss2HPPanel = nullptr;
        Boss3HPPanel = nullptr;


        m_Choice = 0;

        m_EntityList.erase(m_EntityList.begin(), m_EntityList.end());

        std::shared_ptr<Entity> fail = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.5), 0.0f, vec2(1.2, 0.5), vec3(1.0, 1.0, 1.0), 1, 0, FailTexture);
        m_EntityList.push_back(fail);

        std::shared_ptr<Entity> menu1 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, -0.0), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, titleIcon);
        m_EntityList.push_back(menu1);

        std::shared_ptr<Entity> menu2 = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, -0.4), 0.0f, vec2(1, 0.4), vec3(1.0, 1.0, 1.0), 1, 0, exitIcon);
        m_EntityList.push_back(menu2);

        std::shared_ptr<Entity> choice = std::make_shared<Entity>(EntityType::MENU, vec2(0.0, 0.0), 0.0f, vec2(1.2, 0.5), vec3(0.0, 0.0, 0.0), 1, -1);
        m_EntityList.push_back(choice);
    }

    if (m_Choice == 0)
    {
        m_EntityList[3]->m_Position = vec2(0.0, -0.0);
    }
    else
    {
        m_EntityList[3]->m_Position = vec2(0.0, -0.4);
    }

    if (Input::isKeyPressed(GLUT_KEY_UP))
    {
        m_Choice = 0;
    }    
    if (Input::isKeyPressed(GLUT_KEY_DOWN))
    {
        m_Choice = 1;
    }  

    if (Input::isKeyPressed(32))
    {
        lastSpacePress = 0.3;
        if (m_Choice == 0)
        {
            m_CurrentStage = SceneStage::TITLE;
            m_CurrentStageTime = 0;
            return;
        }
        else {
            exit(0);
        }
    }
    m_CurrentStageTime += timestep;
}


void Scene::PlayerMove(std::shared_ptr<Entity> playerEntity, double timestep)
{
    prevChangeState += timestep;
    if (prevChangePlayerTexture < 0)
    {
        prevChangePlayerTexture = 0.1;
        // Update Player Texture
        if (Input::isKeyPressed(GLUT_KEY_LEFT))
        {
            if (moveState != 1) { NormalPointer = -1; }
            moveState = 1;
            NormalPointer += 1;
            if (NormalPointer >= PlayerLeftArray.size()) { NormalPointer -= 1; }
            playerEntity->m_Texture = PlayerLeftArray[NormalPointer];
        }
        else if (Input::isKeyPressed(GLUT_KEY_RIGHT))
        {
            if (moveState != 2) { NormalPointer = -1; }
            moveState = 2;
            NormalPointer += 1;
            if (NormalPointer >= PlayerRightArray.size()) { NormalPointer -= 1; }
            playerEntity->m_Texture = PlayerRightArray[NormalPointer];
        }
        else
        {
            if (moveState == 1)
            {
                NormalPointer -= 1;
                if (NormalPointer < 0) { NormalPointer = 0; moveState = -1; }
                playerEntity->m_Texture = PlayerLeftArray[NormalPointer];
            }
            if (moveState == 2)
            {
                NormalPointer -= 1;
                if (NormalPointer < 0) { NormalPointer = 0; moveState = -1; }
                playerEntity->m_Texture = PlayerRightArray[NormalPointer];
            }
            else {
                moveState = 0;
                NormalPointer += 1;
                if (NormalPointer >= PlayerNormalArray.size()) { NormalPointer = 0; }
                playerEntity->m_Texture = PlayerNormalArray[NormalPointer];
            }
        }

    }
    if (prevChangePlayerTexture >= 0) { 
        if (moveState == 0) {
            prevChangePlayerTexture -= timestep; 
        } else {
            prevChangePlayerTexture -= 2 * timestep;
        }
    }


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

                double xOffset = (double)i - ((double)bulletCount - 1)/2;
                pos = pos + vec2(xOffset * playerSpeed * 0.05, 0.05);
                std::shared_ptr<Entity> playerBullet = std::make_shared<Entity>(EntityType::PLAYER_BULLET, pos, 90.0f, vec2(PLAYER_BULLET_SIZE * 2, PLAYER_BULLET_SIZE * 2), vec3(1.0, 1.0, 1.0), 1.0, 70.0, PlayerBulletTexture);
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
            bossEntity->m_Position.x = 0.999;
            bossEntity->m_Angle = 180;
            Boss1Wait = 2;
        }
        else if (bossEntity->m_Position.x <= -1.0)
        {
            bossEntity->m_Position.x = -0.999;
            bossEntity->m_Angle = 0;
            Boss1Wait = 2;
        }
    }
    else 
    {
        Boss1Wait -= timestep;
    }
}

void Scene::Boss1ShootBullet(std::shared_ptr<Entity> boss1Entity, double timestep)
{
    Boss1currentBigBulletTime += timestep;
    if (Boss1Wait > 0 && (Boss1prevBigBulletTime == 0 || Boss1currentBigBulletTime - Boss1prevBigBulletTime >= 0.5))
    {
        int bulletCount = 9;
        for (int i = 0; i < bulletCount; i++)
        {
            std::shared_ptr<Entity> boss1BigBullet = std::make_shared<Entity>(EntityType::BOSS_BIG_BULLET, boss1Entity->m_Position, ((double)i * 360.0f / (double)bulletCount) + Boss1currentBigBulletTime * 100000, vec2(BOSS_BIG_BULLET_SIZE * 2, BOSS_BIG_BULLET_SIZE * 2), vec3(getRandom(), getRandom(), getRandom()), 1.0, 80.0, BossBigBulletTexture);
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

void Scene::Boss1Die(std::shared_ptr<Entity> boss1Entity, double timestep)
{
    boss1Entity->m_Alpha -= 1 * timestep;
    if (boss1Entity->m_Alpha <= 0.01)
    {
        BOSS1DEAD = true;
    }
}


void Scene::Boss2Move(std::shared_ptr<Entity> bossEntity, double timestep)
{
    if (Boss2Wait <= 0)
    {
        float angleRadians = bossEntity->m_Angle * (M_PI / 180.0);
        bossEntity->m_Position.x += 1 * std::cos(angleRadians) * timestep;
        bossEntity->m_Position.y += 0.5 * std::sin(angleRadians) * timestep;

        if (bossEntity->m_Position.x >= 1.0)
        {
            bossEntity->m_Position.x = 0.999;
            bossEntity->m_Angle = 135;
            Boss2Wait = 2;
        }
        else if (bossEntity->m_Position.y <= 0.0)
        {
            bossEntity->m_Position.y = 0.001;
            bossEntity->m_Angle = 45;
            Boss2Wait = 2;
        }
        else if (bossEntity->m_Position.x <= -1.0)
        {
            bossEntity->m_Position.x = -0.999;
            bossEntity->m_Angle = 315;
            Boss2Wait = 2;
        }
        else if (bossEntity->m_Position.y >= 1.0)
        {
            bossEntity->m_Position.y = 0.999;
            bossEntity->m_Angle = 225;
            Boss2Wait = 2;
        }
    }
    else 
    {
        Boss2Wait -= timestep;
    }
}

void Scene::Boss2ShootBullet(std::shared_ptr<Entity> boss2Entity, double timestep)
{
    Boss2currentBigBulletTime += timestep;
    if (Boss2Wait > 0 && (Boss2prevBigBulletTime == 0 || Boss2currentBigBulletTime - Boss2prevBigBulletTime >= 0.05))
    {
        int bulletCount = 6;
        for (int i = 0; i < bulletCount; i++)
        {
            std::shared_ptr<Entity> boss2SmallBullet = std::make_shared<Entity>(EntityType::BOSS_SMALL_BULLET, boss2Entity->m_Position, getRandom() * 360.0f, 
            vec2(BOSS_SMALL_BULLET_SIZE * 2, BOSS_SMALL_BULLET_SIZE * 2), vec3(1.0, 1.0, getRandom()), 1.0, 80.0, BossSmallBulletTexture);            
            m_EntityList.push_back(boss2SmallBullet);
        }
        Boss2prevBigBulletTime = Boss2currentBigBulletTime;
    }
}

void Scene::Boss2BulletMove(std::shared_ptr<Entity> boss2BulletEntity, double timestep)
{
    float angleRadians = boss2BulletEntity->m_Angle * (M_PI / 180.0);

    boss2BulletEntity->m_Position.x += 1 * std::cos(angleRadians) * timestep;
    boss2BulletEntity->m_Position.y += 1 * std::sin(angleRadians) * timestep;
}

void Scene::Boss2Die(std::shared_ptr<Entity> boss2Entity, double timestep)
{
    boss2Entity->m_Alpha -= 1 * timestep;
    if (boss2Entity->m_Alpha <= 0.01)
    {
        BOSS2DEAD = true;
    }
}



void Scene::Boss3Move(std::shared_ptr<Entity> bossEntity, std::shared_ptr<Entity> playerEntity, double timestep)
{
    if (Boss3Mode == 0)
    {
        if (Boss3MoveTime <= 0)
        {
            Boss3MoveTime = 5;
        }

        double Boss3Speed = 2;
        float angleRadians = bossEntity->m_Angle * (M_PI / 180.0);
        bossEntity->m_Position.x += Boss3Speed * std::cos(angleRadians) * timestep;
        bossEntity->m_Position.y += 0.5 * std::sin(angleRadians) * timestep;

        if (bossEntity->m_Position.x >= 1.5)
        {
            bossEntity->m_Position.x = 1.499;
            bossEntity->m_Angle = 180;
        }
        else if (bossEntity->m_Position.x <= -1.5)
        {
            bossEntity->m_Position.x = -1.499;
            bossEntity->m_Angle = 0;
        }

        Boss3MoveTime -= timestep;
        if (Boss3MoveTime <= 0)
        {
            Boss3Mode = 1;
        }
    }

    else if (Boss3Mode == 1)
    {
        if (!playerEntity) { return; }
        if (Boss3ShootTime <= 0)
        {
            double Boss3prevBigBulletTime = 0;
            double Boss3currentBigBulletTime = 0;
            Boss3ShootTime = 5;
        }

        Boss2currentBigBulletTime += timestep;
        if (Boss3ShootTime < 4.5 && (Boss3prevBigBulletTime == 0 || Boss3currentBigBulletTime - Boss3prevBigBulletTime >= 0.3))
        {
            vec2 Direction = playerEntity->m_Position - bossEntity->m_Position;
            double angle = atan(Direction.y / Direction.x) * 180 / 3.1415926;
            if (Direction.x < 0) { angle = angle + 180; }
            std::shared_ptr<Entity> boss3BigBullet = std::make_shared<Entity>(EntityType::BOSS_BIG_BULLET, bossEntity->m_Position, angle, 
            vec2(BOSS_BIG_BULLET_SIZE * 2, BOSS_BIG_BULLET_SIZE * 2), vec3(0.0, 0.2, 0.5), 1.0, 80.0, BossBigBulletTexture);            
            m_EntityList.push_back(boss3BigBullet);
            Boss3prevBigBulletTime = Boss3currentBigBulletTime;
        }

        Boss3ShootTime -= timestep;

        if (Boss3ShootTime <= 0)
        {
            Boss3Mode = 2;
        }
    }

    else if (Boss3Mode == 2)
    {
        if (Boss3WaitTime <= 0)
        {
            Boss3WaitTime = 3;
        }

        Boss3WaitTime -= timestep;

        if (Boss3WaitTime <= 0)
        {
            Boss3Mode = 0;
        }
    }
}

void Scene::Boss3ShootBullet(std::shared_ptr<Entity> boss3Entity, double timestep)
{
    Boss3currentBigBulletTime += timestep;
    if (Boss3Mode == 0)
    {
        if (getRandom() > 0.0001)
        {
            std::shared_ptr<Entity> boss3SmallBullet = std::make_shared<Entity>(EntityType::BOSS_SMALL_BULLET, boss3Entity->m_Position, -90 + 360 * (getRandom()-0.5), 
            vec2(BOSS_SMALL_BULLET_SIZE * 2, BOSS_SMALL_BULLET_SIZE * 2), vec3(0.0, 1.0, 0.0), 1.0, 80.0, BossSmallBulletTexture);            
            m_EntityList.push_back(boss3SmallBullet);
        }
    }

    if (Boss3Mode == 1)
    {
    }

    else if (Boss3Mode == 2)
    {

    }
}

void Scene::Boss3BulletMove(std::shared_ptr<Entity> boss3BulletEntity, double timestep)
{
    double speed = 2;
    if (boss3BulletEntity->m_EntityType == EntityType::BOSS_SMALL_BULLET) { speed = 0.3; }
    float angleRadians = boss3BulletEntity->m_Angle * (M_PI / 180.0);

    boss3BulletEntity->m_Position.x += speed * std::cos(angleRadians) * timestep;
    boss3BulletEntity->m_Position.y += speed * std::sin(angleRadians) * timestep;
}

void Scene::Boss3Die(std::shared_ptr<Entity> boss3Entity, double timestep)
{
    boss3Entity->m_Alpha -= 1 * timestep;
    if (boss3Entity->m_Alpha <= 0.01)
    {
        BOSS3DEAD = true;
    }
}



void Scene::PlayerDie(std::shared_ptr<Entity> playerEntity, double timestep)
{
    playerEntity->m_Alpha -= 1 * timestep;
    if (playerEntity->m_Alpha <= 0.01)
    {
        PLAYERDEAD = true;
    }
}






void Scene::OnUpdateTest(double timestep)
{
    if (m_CurrentStageTime == 0)
    {
        std::shared_ptr<Texture> texture = Texture::Create("Start.png");
        std::shared_ptr<Entity> playerBullet = std::make_shared<Entity>(EntityType::PLAYER_BULLET, vec2(0.0, 0.0), 90.0f, vec2(0.5, 0.5), vec3(1.0, 1.0, 1.0), 1.0, 70.0, PlayerBulletTexture);
        m_EntityList.push_back(playerBullet);
    }
    m_CurrentStageTime += 1;
}