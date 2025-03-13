#pragma once

#include "DxLib.h"
#include "Input.h"
#include "Vec3.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Update(Input& input);
	void Draw();

	void OnDamage();
	Vec3 GetPos() const { return m_pos; }
	bool IsLockOn() const { return m_isLockOn; }

private:
	// �v���C���[�̃��f��
	int m_model;
	// �A�j���[�V�����n���h��
	int m_anim;
	// �v���C���[�̈ʒu
	Vec3 m_pos;
	// �v���C���[�̈ړ���
	Vec3 m_vec;
	// �v���C���[�̌����Ă������
	float m_angle;
	// �v���C���[�̉�]�s��
	MATRIX m_rotMtx;
	// �v���C���[��HP
	int m_hp;
	// ���b�N�I���t���O
	bool m_isLockOn;
	// �W�����v
	bool m_isJump;

	// �o�߃t���[���𑪂�
	float m_frameCount;
};

