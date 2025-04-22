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

	// �X�V
	void Update(std::shared_ptr<Player> player);
	// �`��
	void Draw();

	// �G�̈ʒu���擾
	Vec3 GetPos() const { return m_pos; }
	// �G�̓����蔻��̈ʒu���擾
	Vec3 GetColPos() const;
	// �G�̔��a���擾
	float GetRadius() const;
	// �G�����͈͂��O���Ƀ����_���Ő������邽�߂̊֐�
	Vec3 GeneratePos();

private:
	// �G�̃��f��
	int m_model;
	// �G�̈ʒu
	Vec3 m_pos;
	Vec3 m_moveVec;
	// �G�̃X�s�[�h
	float m_speed;
	// �t���[����
	int m_frame;

	void IdleUpdate(std::shared_ptr<Player> player);
	void RunUpdate(std::shared_ptr<Player> player);
	void DeadUpdate(std::shared_ptr<Player> player);

	// ��ԑJ�ڂ̂��߂̕ϐ�
	using UpdateFunc_t = void (Enemy::*)(std::shared_ptr<Player> player);
	// ��Ԃɍ��킹�������o�֐��|�C���^
	UpdateFunc_t m_update;
};

