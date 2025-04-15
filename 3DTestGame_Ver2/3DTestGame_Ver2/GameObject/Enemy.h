#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include <memory>

class Player;
class Enemy
{
public:
	Enemy();
	~Enemy();

	// �X�V�A�`��
	void Update(std::shared_ptr<Player> player);
	void Draw();

	// �G�l�~�[�̈ʒu���擾
	Vec3 GetPos() const { return m_pos; }
	// �G�l�~�[�̔��a���擾
	float GetRadius() const { return m_radius; }

private:
	// �G�l�~�[�̈ʒu
	Vec3 m_pos;
	// ���̔��a
	float m_radius;
};

