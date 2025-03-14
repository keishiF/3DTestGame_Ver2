#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include <memory>

class Player;
class Enemy;
class Camera
{
public:
	Camera();
	~Camera();
	void Update(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);
	void SetCamera(std::shared_ptr<Player> player);

private:
	// �J�����̈ʒu
	Vec3 m_pos;
	// �J�����̒����_
	Vec3 m_lookAtPos;
	// �J�����̎���p
	float m_fov;
	// �J�����̉�]��
	float m_cameraRot;
	// ���b�N�I���t���O
	bool m_isLockOn;
};

