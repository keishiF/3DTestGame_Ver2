#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>
#include <iostream>

namespace
{
    // 敵の移動速度
    constexpr float kSpeed = 20.0f;
    // 再生成毎の敵の速度の上昇量
    constexpr float kUpSpeed = 0.2f;
    // 敵の半径
    constexpr float kColRadius = 80.0f;
    // 敵が生成される範囲
    constexpr float kGenerateRange = 750.0f;
    // フィールドの端
    constexpr float kField = 800.0f;
}

Enemy::Enemy() :
    m_model(-1),
	m_pos(10000.0f, 10000.0f, 10000.0f),
	m_moveVec(0.0f, 0.0f, 0.0f),
    m_speed(kSpeed),
    m_frame(0),
	m_update(&Enemy::IdleUpdate)
{
    // モデルの読み込み
    m_model = MV1LoadModel("Data/Model/Enemy/Enemy.mv1");
    assert(m_model != -1);

    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

Enemy::~Enemy()
{
    MV1DeleteModel(m_model);
}

void Enemy::IdleUpdate(std::shared_ptr<Player> player)
{
    // ランダムな位置に生成
    m_pos = GeneratePos();
    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));

    // プレイヤーに向かうベクトルを取得
	Vec3 playerPos = player->GetPos();
    Vec3 enemyToPlayer = playerPos - m_pos;
	enemyToPlayer.Normalize();
    m_moveVec = enemyToPlayer * m_speed;

    // 突進状態に移行
    m_update = &Enemy::RunUpdate;
}

void Enemy::RunUpdate(std::shared_ptr<Player> player)
{
    // 敵を移動
    m_pos.x += m_moveVec.x;
    m_pos.z += m_moveVec.z;
    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));

    // フィールドの外に出たら再生成する
    if (m_pos.x > kField)
    {
        m_speed += kUpSpeed;
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.x < -kField)
    {
        m_speed += kUpSpeed;
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.z > kField)
    {
        m_speed += kUpSpeed;
        m_update = &Enemy::IdleUpdate;
    }
    if (m_pos.z < -kField)
    {
        m_speed += kUpSpeed;
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

Vec3 Enemy::GeneratePos()
{
    // 一定の範囲でランダムな値を生成
    int randPos = GetRand(kGenerateRange * 2) - kGenerateRange;

    float fieldSize = kGenerateRange;
    if (GetRand(1) == 0)
    {
        fieldSize *= -1;
    }

    if (GetRand(1) == 0)
    {
        return Vec3(static_cast<float>(randPos), 0.0f, fieldSize);
    }
    else
    {
        return Vec3(fieldSize, 0.0f, static_cast<float>(randPos));
    }
}
