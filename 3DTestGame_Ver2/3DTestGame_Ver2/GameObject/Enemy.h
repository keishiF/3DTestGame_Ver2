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

	// �G�̈ʒu���擾
	Vec3 GetPos() const { return m_pos; }
	// �G�̓����蔻��̈ʒu���擾
	Vec3 GetColPos() const;
	// �G�̔��a���擾
	float GetRadius() const;

private:
	// �G�̃��f��
	int m_model;
	// �G�̈ʒu
	Vec3 m_pos;
};

