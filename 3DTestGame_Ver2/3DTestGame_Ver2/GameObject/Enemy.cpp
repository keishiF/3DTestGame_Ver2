#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() :
	m_pos(0.0f, 150.0f, 0.0f),
	m_hp(3)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), 100.0f, 16, 0xff0000, 0xff0000, true);
}

void Enemy::Ondamage()
{
	m_hp--;
}
