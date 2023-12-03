#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "Render/Texture.h"
#include "BossHPPanel.h"

enum class SceneStage
{
    TITLE,
    CHOOSE_CHARACTER,

    CONVERSATION1,
    BOSSFIGHT1,
    VICTORY1,

    CONVERSATION2,
    BOSSFIGHT2,
    VICTORY2,

    CONVERSATION3,
    BOSSFIGHT3,
    VICTORY3,

    FAILED,

    BADEND,
    END
};

class Scene
{
public:
    Scene();
    ~Scene() = default;

    void OnUpdate(double timestep);
    void OnDisplay();

    void OnUpdateTest(double timestep);

    void OnUpdateTitle(double timestep);
    void OnUpdateChooseCharacter(double timestep);
    void OnUpdateConversation1(double timestep);
    void OnUpdateBossfight1(double timestep);
    void OnUpdateVictory1(double timestep);
    void OnUpdateFailed(double timestep);

    void PlayerMove(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerShootBullet(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerBulletMove(std::shared_ptr<Entity> playerBulletEntity, double timestep);
    void PlayerDie(std::shared_ptr<Entity> playerEntity, double timestep);
    void Boss1Move(std::shared_ptr<Entity> bossEntity, double timestep);
    void Boss1ShootBullet(std::shared_ptr<Entity> boss1Entity, double timestep);
    void Boss1BulletMove(std::shared_ptr<Entity> boss1BulletEntity, double timestep);
    void Boss1Die(std::shared_ptr<Entity> boss1BulletEntity, double timestep);

    // Collision volume
    double PLAYER_RADIUS = 0.02;
    double BOSS_RADIUS = 0.1;
    double PLAYER_BULLET_RADIUS = 0.02;
    double BOSS_SMALL_BULLET_RADIUS = 0.02;
    double BOSS_BIG_BULLET_RADIUS = 0.05;



    SceneStage m_CurrentStage = SceneStage::TITLE;
    double m_CurrentStageTime = 0;



    std::vector<std::shared_ptr<Entity>> m_EntityList;
    std::shared_ptr<Entity> m_Player;
    std::vector<std::shared_ptr<Entity>> m_PlayerBullets;

    std::shared_ptr<Entity> m_Boss1;
    std::shared_ptr<BossHPPanel> Boss1HPPanel;
    double Boss1HP = 100;
    int Boss1MaxMode = 3;
    int Boss1Mode = 0;
    double Boss1Wait = 0;  // Wait 
    double Boss1prevBigBulletTime = 0;
    double Boss1currentBigBulletTime = 0;
    bool BOSS1DEAD = false;


    bool PLAYERDEAD = false;
    int playerLives = 2;
    double playerSpeed = 1.5;
    double prevBulletTime = 0;
    double currentBulletTime = 0;
    int flashUnit = 0;

    std::shared_ptr<Texture> texture;
};