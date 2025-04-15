#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"

namespace
{
    // エネミーの移動速度
    constexpr float kSpeed = 5.0f;
    // エネミーの半径
    constexpr float kRadius = 100.0f;
}

Enemy::Enemy() :
	m_pos(0.0f, 150.0f, 0.0f),
	m_radius(kRadius)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(std::shared_ptr<Player> player)
{
    // プレイヤーの位置を取得
    Vec3 playerPos = player->GetPos();

    // プレイヤーの位置に向かう方向を計算
    Vec3 direction = {
        playerPos.x - m_pos.x,
        playerPos.y - m_pos.y,
        playerPos.z - m_pos.z
    };

    // 距離を計算
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

    // 正規化して方向ベクトルを単位ベクトルにする
    if (distance > 0.0f)
    {
        direction.x /= distance;
        direction.y /= distance;
        direction.z /= distance;
    }

    // エネミーを移動
    m_pos.x += direction.x * kSpeed;
    m_pos.y += direction.y * kSpeed;
    m_pos.z += direction.z * kSpeed;
}

void Enemy::Draw()
{
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), m_radius, 16, 0x00ff00, 0x00ff00, true);
}
