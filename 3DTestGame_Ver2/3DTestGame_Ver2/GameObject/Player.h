#pragma once

#include "DxLib.h"
#include "Input.h"
#include "Vec3.h"
#include <memory>

class Camera;
class Player
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	Player();
	virtual ~Player();

	// �X�V�A�`��
	void Update(Input& input, std::shared_ptr<Camera> camera);
	void Draw();

	// �_���[�W���󂯂����̏������܂Ƃ߂�֐�
	void OnDamage();

	// �ʒu�̎擾
	Vec3 GetPos() const { return m_pos; }
	// ��]�s��̎擾
	MATRIX GetRotMtx() const { return m_rotMtx; }
	// ���b�N�I�����Ă��邩�̎擾
	bool IsLockOn() const { return m_isLockOn; }

private:
	// �W�����v�֘A�̊֐�
	void StartJump();
	void UpdateJump();

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
	// �W�����v���
	bool m_isJump;
	float m_jumpSpeed;
	float m_gravity;

	// �o�߃t���[���𑪂�
	float m_frameCount;
};

