#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>

namespace
{
    // �G�̈ړ����x
    constexpr float kSpeed = 5.0f;
    // �G�̔��a
    constexpr float kColRadius = 80.0f;
}

Enemy::Enemy() :
    m_model(-1),
	m_pos(0.0f, 150.0f, 0.0f)
{
    m_model = MV1LoadModel("Data/Model/Enemy.mv1");
    assert(m_model != -1);

    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

Enemy::~Enemy()
{
    MV1DeleteModel(m_model);
}

void Enemy::Update(std::shared_ptr<Player> player)
{
    // �v���C���[�̈ʒu���擾
    Vector3 playerPos = player->GetPos();

    // �v���C���[�̈ʒu�Ɍ������������v�Z
    Vector3 direction = {
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

    // �G���ړ�
    m_pos.x += direction.x * kSpeed;
    m_pos.y += direction.y * kSpeed;
    m_pos.z += direction.z * kSpeed;

    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

void Enemy::Draw()
{
    MV1DrawModel(m_model);

#ifdef _DEBUG
    DrawSphere3D(VGet(GetColPos().x, GetColPos().y, GetColPos().z), kColRadius, 16, 0xff00ff, 0xff00ff, false);
#endif
}

Vector3 Enemy::GetColPos() const
{
    Vector3 result = m_pos;
    result.y += 64.0f;
    return result;
}

float Enemy::GetRadius() const
{
    return kColRadius;
}
