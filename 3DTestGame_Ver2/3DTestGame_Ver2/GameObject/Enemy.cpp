#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>
#include <iostream>
#include <random>

namespace
{
    // �G�̈ړ����x
    constexpr float kSpeed = 5.0f;
    // �G�̔��a
    constexpr float kColRadius = 80.0f;
    // �G�����������͈�
    constexpr float kGenerateRangeMin = -500.0f;
    constexpr float kGenerateRangeMax =  500.0f;
    constexpr float kSpawnBuffer      =  50.0f;
}

Enemy::Enemy() :
    m_model(-1),
	m_pos(),
	m_moveVec(0.0f, 0.0f, 0.0f),
	m_update(&Enemy::IdleUpdate)
{
    m_model = MV1LoadModel("Data/Enemy/Enemy.mv1");
    assert(m_model != -1);

    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

Enemy::~Enemy()
{
    MV1DeleteModel(m_model);
}

void Enemy::IdleUpdate(std::shared_ptr<Player> player)
{
    m_pos = GeneratePos(player);
    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	Vec3 playerPos = player->GetPos();
    Vec3 enemyToPlayer = playerPos - m_pos;
	enemyToPlayer.Normalize();
    m_moveVec = enemyToPlayer * kSpeed;

    m_update = &Enemy::RunUpdate;
}

void Enemy::RunUpdate(std::shared_ptr<Player> player)
{
    // �G���ړ�
    m_pos.x += m_moveVec.x;
    m_pos.z += m_moveVec.z;

    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));

    if (m_pos.x > 700.0f)
    {
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.x < -700.0f)
    {
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.z > 700.0f)
    {
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.z < -700.0f)
    {
        m_update = &Enemy::IdleUpdate;
    }
}

void Enemy::DeadUpdate(std::shared_ptr<Player> player)
{
}

void Enemy::Update(std::shared_ptr<Player> player)
{
    (this->*m_update)(player);
}

void Enemy::Draw()
{
    MV1DrawModel(m_model);

#ifdef _DEBUG
    DrawSphere3D(VGet(GetColPos().x, GetColPos().y, GetColPos().z), kColRadius, 16, 0xff00ff, 0xff00ff, false);
#endif
}

Vec3 Enemy::GetColPos() const
{
    Vec3 result = m_pos;
    result.y += 64.0f;
    return result;
}

float Enemy::GetRadius() const
{
    return kColRadius;
}

Vec3 Enemy::GeneratePos(std::shared_ptr<Player> player)
{
    // ��ӂ̒������̗����𐶐�
    // 
    // x��z�̂ǂ��炩���Œ肵�A�ǂ��炩�ɐ��������������[�Ă�
    // 
    // �Œ肵�����������_���ɔ��]������/



    //static std::random_device rd;
    //static std::mt19937 gen(rd());
    //static std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);

    //Vec3 position;
    //do
    //{
    //    position.x = dist(gen);
    //    position.z = dist(gen);
    //} while (position.x > kGenerateRangeMin - kSpawnBuffer && 
    //    position.x < kGenerateRangeMax + kSpawnBuffer &&
    //    position.z > kGenerateRangeMin - kSpawnBuffer && 
    //    position.z < kGenerateRangeMax + kSpawnBuffer);

    //position.y = 0.0f; // Y���W�͌Œ�
    //return position;
}
