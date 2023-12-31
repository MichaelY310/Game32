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

    CONVERSATION2,
    BOSSFIGHT2,

    CONVERSATION3,
    BOSSFIGHT3,

    SUCCEED,
    RESTART,
    FAILED,
    LEADERBOARD,

    BADEND,
    END
};

class Scene
{
public:
    Scene();
    ~Scene() = default;
    void Init();

    void OnUpdate(double timestep);
    void OnDisplay();

    void OnUpdateTest(double timestep);

    void OnUpdateTitle(double timestep);
    void OnUpdateChooseCharacter(double timestep);
    void OnUpdateConversation1(double timestep);
    void OnUpdateBossfight1(double timestep);
    void OnUpdateConversation2(double timestep);
    void OnUpdateBossfight2(double timestep);
    void OnUpdateConversation3(double timestep);
    void OnUpdateBossfight3(double timestep);
    void OnUpdateLeaderBoard(double timestep);

    void OnUpdateSucceed(double timestep);
    void OnUpdateFailed(double timestep);

    void PlayerMove(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerShootBullet(std::shared_ptr<Entity> playerEntity, double timestep);
    void PlayerBulletMove(std::shared_ptr<Entity> playerBulletEntity, double timestep);
    void PlayerDie(std::shared_ptr<Entity> playerEntity, double timestep);

    void Boss1Move(std::shared_ptr<Entity> bossEntity, double timestep);
    void Boss1ShootBullet(std::shared_ptr<Entity> boss1Entity, double timestep);
    void Boss1BulletMove(std::shared_ptr<Entity> boss1BulletEntity, double timestep);
    void Boss1Die(std::shared_ptr<Entity> boss1BulletEntity, double timestep);

    void Boss2Move(std::shared_ptr<Entity> bossEntity, double timestep);
    void Boss2ShootBullet(std::shared_ptr<Entity> boss2Entity, double timestep);
    void Boss2BulletMove(std::shared_ptr<Entity> boss2BulletEntity, double timestep);
    void Boss2Die(std::shared_ptr<Entity> boss2BulletEntity, double timestep);

    void Boss3Move(std::shared_ptr<Entity> bossEntity, std::shared_ptr<Entity> playerEntity, double timestep);
    void Boss3ShootBullet(std::shared_ptr<Entity> boss3Entity, double timestep);
    void Boss3BulletMove(std::shared_ptr<Entity> boss3BulletEntity, double timestep);
    void Boss3Die(std::shared_ptr<Entity> boss3BulletEntity, double timestep);

    // Collision volume
    double PLAYER_RADIUS = 0.02;
    double BOSS_RADIUS = 0.1;
    double PLAYER_BULLET_RADIUS = 0.02;
    double BOSS_SMALL_BULLET_RADIUS = 0.02;
    double BOSS_BIG_BULLET_RADIUS = 0.1;

    double PLAYER_SIZE = 0.08;
    double BOSS_SIZE = 0.1;
    double PLAYER_BULLET_SIZE = 0.02;
    double BOSS_SMALL_BULLET_SIZE = 0.03;
    double BOSS_BIG_BULLET_SIZE = 0.12;



    SceneStage m_CurrentStage = SceneStage::TITLE;

    double m_CurrentStageTime = 0;



    std::vector<std::shared_ptr<Entity>> m_EntityList;
    std::shared_ptr<Entity> m_Player;
    std::vector<std::shared_ptr<Entity>> m_PlayerBullets;

    std::shared_ptr<Entity> m_Boss1;
    std::shared_ptr<Entity> m_Boss2;
    std::shared_ptr<Entity> m_Boss3;
    std::shared_ptr<BossHPPanel> Boss1HPPanel;
    std::shared_ptr<BossHPPanel> Boss2HPPanel;
    std::shared_ptr<BossHPPanel> Boss3HPPanel;

    double Boss1HP = 100;
    int Boss1MaxMode = 3;
    int Boss1Mode = 0;
    double Boss1Wait = 0;  // Wait 
    double Boss1prevBigBulletTime = 0;
    double Boss1currentBigBulletTime = 0;
    bool BOSS1DEAD = false;

    double Boss2HP = 100;
    int Boss2MaxMode = 3;
    int Boss2Mode = 0;
    double Boss2Wait = 0;  // Wait 
    double Boss2prevBigBulletTime = 0;
    double Boss2currentBigBulletTime = 0;
    bool BOSS2DEAD = false;

    double Boss3HP = 100;
    int Boss3MaxMode = 3;
    int Boss3Mode = 0; // Move: 0, Shoot: 1, Wait: 2
    double Boss3MoveTime = 0;
    double Boss3ShootTime = 0;
    double Boss3WaitTime = 0;  // Wait 
    double Boss3prevBigBulletTime = 0;
    double Boss3currentBigBulletTime = 0;
    bool BOSS3DEAD = false;


    bool PLAYERDEAD = false;
    int playerLives = 2;
    int playerATK = 5;
    double playerSpeed = 1.5;
    double prevBulletTime = 0;
    double currentBulletTime = 0;
    int flashUnit = 0;


    // GameUI
    int m_Choice = 0;
    double lastClick = 0;
    double lastSpacePress = 0;
    double BlackCoverTime = 0;
    double MaxBlackCoverTime = 300;


    std::shared_ptr<Texture> startIcon;
    std::shared_ptr<Texture> titleIcon;
    std::shared_ptr<Texture> How_To_Play_Icon;
    std::shared_ptr<Texture> exitIcon;
    std::shared_ptr<Texture> FailTexture;
    std::shared_ptr<Texture>  SuccessIcon;


    double prevChangeState = 0;
    int moveState = 0;

    std::shared_ptr<Texture> PlayerNormal;
    std::vector<std::shared_ptr<Texture>> PlayerNormalArray;
    int NormalPointer = 0;
    double prevChangePlayerTexture = 0;

    std::shared_ptr<Texture> PlayerRight;
    std::vector<std::shared_ptr<Texture>> PlayerLeftArray;

    std::shared_ptr<Texture> PlayerLeft;
    std::vector<std::shared_ptr<Texture>> PlayerRightArray;

    std::shared_ptr<Texture> Boss1Texture;
    std::shared_ptr<Texture> Boss2Texture;
    std::shared_ptr<Texture> Boss3Texture;

    std::shared_ptr<Texture> BossBigBulletTexture;
    std::shared_ptr<Texture> BossSmallBulletTexture;
    std::shared_ptr<Texture> PlayerBulletTexture;

    std::shared_ptr<Texture> PlayerLivesTexture;
    std::shared_ptr<Texture> HowToPlayTexture;

    std::shared_ptr<Texture> Background1;
    std::shared_ptr<Texture> Background2;
    std::shared_ptr<Texture> Background3;

    double TimeUsed = 0;
    std::vector<double> Leaders;


    bool IsDisplayHowToPlay = false;
    int tempFollow = 0;

    vec2 background2Pos = vec2(0, 0);
    vec2 background3Pos = vec2(0, -2);
};