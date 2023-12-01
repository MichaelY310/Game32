#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "Render/Texture.h"

enum class SceneStage
{
    TITLE,
    CHOOSE_CHARACTER,
    CONVERSATION1,
    BOSSFIGHT1,
    CONVERSATION2,
    BOSSFIGHT2,
    CONVERSATION3,
    BOSSFIGHT3,
    END,
};

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void OnUpdate(double timestep);
    void OnDisplay();

    void OnUpdateTitle(double timestep);
    void OnUpdateChooseCharacter(double timestep);
    void OnUpdateConversation1(double timestep);
    void OnUpdateBossfight1(double timestep);


    void PlayerMove(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerShootBullet(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerBulletMove(std::shared_ptr<Entity> playerBulletEntity, double timestep);
    void Boss1Move(std::shared_ptr<Entity> playerEntity, double timestep);



    SceneStage m_CurrentStage = SceneStage::TITLE;
    double m_CurrentStageTime = 0;



    std::vector<std::shared_ptr<Entity>> m_EntityList;
    std::shared_ptr<Entity> m_Player;
    std::vector<std::shared_ptr<Entity>> m_PlayerBullets;

    std::shared_ptr<Entity> m_Boss1;
    int Boss1HP = 100;
    int Boss1MaxMode = 3;
    int Boss1Mode = 0;


    double playerSpeed = 1.5;
    double prevBulletTime = 0;
    double currentBulletTime = 0;

    std::shared_ptr<Texture> texture;
};