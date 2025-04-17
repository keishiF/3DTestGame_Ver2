#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include "Input.h"
#include <memory>

class Player;
class Enemy;
class Camera
{
public:
	Camera();
	~Camera();
	// �X�V����
	void Update(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);
	// �J�����̏�����
	void SetCamera(std::shared_ptr<Player> player);

	// �J�����̉�]�s����擾
	float GetCamRotX() const { return m_cameraRotX; }
	float GetCamRotY() const { return m_cameraRotY; }

private:
	// �J�����̈ʒu
	Vec3 m_pos;
	// �J�����̒����_
	Vec3 m_lookAtPos;
	// �J�����̎���p
	float m_fov;
	// �J�����̉�]��
	float m_cameraRotX;
	float m_cameraRotY;
	// ���b�N�I���t���O
	bool m_isLockOn;
};

