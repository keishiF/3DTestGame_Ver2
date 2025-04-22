#include "Enemy.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>
#include <iostream>

namespace
{
    // �G�̈ړ����x
    constexpr float kSpeed = 20.0f;
    // �Đ������̓G�̑��x�̏㏸��
    constexpr float kUpSpeed = 0.2f;
    // �G�̔��a
    constexpr float kColRadius = 80.0f;
    // �G�����������͈�
    constexpr float kGenerateRange = 750.0f;
    // �t�B�[���h�̒[
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
    // ���f���̓ǂݍ���
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
    // �����_���Ȉʒu�ɐ���
    m_pos = GeneratePos();
    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));

    // �v���C���[�Ɍ������x�N�g�����擾
	Vec3 playerPos = player->GetPos();
    Vec3 enemyToPlayer = playerPos - m_pos;
	enemyToPlayer.Normalize();
    m_moveVec = enemyToPlayer * m_speed;

    // �ːi��ԂɈڍs
    m_update = &Enemy::RunUpdate;
}

void Enemy::RunUpdate(std::shared_ptr<Player> player)
{
    // �G���ړ�
    m_pos.x += m_moveVec.x;
    m_pos.z += m_moveVec.z;
    MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));

    // �t�B�[���h�̊O�ɏo����Đ�������
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
    // ���͈̔͂Ń����_���Ȓl�𐶐�
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
