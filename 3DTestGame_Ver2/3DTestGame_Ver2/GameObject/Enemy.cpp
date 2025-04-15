#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"

namespace
{
    // �G�l�~�[�̈ړ����x
    constexpr float kSpeed = 5.0f;
    // �G�l�~�[�̔��a
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
    // �v���C���[�̈ʒu���擾
    Vec3 playerPos = player->GetPos();

    // �v���C���[�̈ʒu�Ɍ������������v�Z
    Vec3 direction = {
        playerPos.x - m_pos.x,
        playerPos.y - m_pos.y,
        playerPos.z - m_pos.z
    };

    // �������v�Z
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

    // ���K�����ĕ����x�N�g����P�ʃx�N�g���ɂ���
    if (distance > 0.0f)
    {
        direction.x /= distance;
        direction.y /= distance;
        direction.z /= distance;
    }

    // �G�l�~�[���ړ�
    m_pos.x += direction.x * kSpeed;
    m_pos.y += direction.y * kSpeed;
    m_pos.z += direction.z * kSpeed;
}

void Enemy::Draw()
{
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), m_radius, 16, 0x00ff00, 0x00ff00, true);
}
