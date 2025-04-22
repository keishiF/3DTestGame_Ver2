#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <algorithm>

namespace
{
	constexpr float kLerpRate = 0.05f;
	constexpr float kRotSpeed = 0.00005f;

	constexpr float kCameraOffsetX = 0.0f;
	constexpr float kCameraOffsetY = 1000.0f;
	constexpr float kCameraOffsetZ = 1000.0f;
}

Camera::Camera() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_lookAtPos(0.0f, 0.0f, 0.0f),
	m_fov(DX_PI_F / 3.0f),
	m_cameraRotX(0.0f),
	m_cameraRotY(0.0f),
	m_isLockOn(false)
{
}

Camera::~Camera()
{
}

void Camera::Update(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	// �v���C���[�ƃG�l�~�[�̈ʒu���擾
	Vec3 playerPos = player->GetPos();
	Vec3 enemyPos = enemy->GetPos();

	// �J�����̈ʒu��␳����l�̐ݒ�
	Vec3 offset = { kCameraOffsetX, kCameraOffsetY, kCameraOffsetZ };

	// �J�����̈ʒu���v���C���[�̈ʒu�Ɋ�Â��čX�V
	m_pos = playerPos;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	// ���b�N�I�����Ă��邩�ǂ���
	m_isLockOn = player->IsLockOn();

	int inputX, inputY;

	//// ���b�N�I�����Ă��Ȃ��Ƃ������J��������]�ł���悤�ɂ���
	//if (!m_isLockOn)
	//{
	//	// �E�X�e�B�b�N�̓��͂��擾
	//	GetJoypadAnalogInputRight(&inputX, &inputY, DX_INPUT_PAD1);

	//	// �J�����̉�]���W���C�p�b�h�̓��͂Ɋ�Â��čX�V
	//	if (inputX != 0)
	//	{
	//		m_cameraRotX += inputX * kRotSpeed;
	//	}

	//	if (inputY != 0)
	//	{
	//		m_cameraRotY += inputY * kRotSpeed;
	//		// �c��]�ɐ�����t����
	//		m_cameraRotY = std::clamp(m_cameraRotY, -DX_PI_F / 3.0f, DX_PI_F / 5.80f);
	//	}
	//}

	// ���b�N�I�����Ă��鎞��
	// �v���C���[�ƃG�l�~�[�̒��Ԓn�_�𒍎��_�ɂ���
	if (m_isLockOn)
	{
		Vec3 targetPos = (playerPos + enemyPos) * 0.5f;
		targetPos.y += 150.0f;
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}
	// ���b�N�I�����Ă��Ȃ�����
	// �v���C���[�̈ʒu�𒍎��_�ɂ���
	else if (!m_isLockOn)
	{
		Vec3 targetPos = { playerPos.x, playerPos.y + 175.0f, playerPos.z - 150.0f };
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}

	// �J�����̈ʒu����]�Ɋ�Â��čX�V
	Vec3 rotatedOffset = {
		offset.x * cos(m_cameraRotX) - offset.z * sin(m_cameraRotX),
		offset.y * cos(m_cameraRotY) - offset.z * sin(m_cameraRotY),
		offset.x * sin(m_cameraRotX) + offset.z * cos(m_cameraRotX)
	};
	m_pos = playerPos + rotatedOffset;

#ifdef _DEBUG
	DrawSphere3D(VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z), 20.0f, 16, 0xffffff, 0xffffff, true);
#endif

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}

void Camera::SetCamera(std::shared_ptr<Player> player)
{
	// �v���C���[�̈ʒu���擾
	Vec3 playerPos = player->GetPos();

	// �J�����̈ʒu��␳����l�̐ݒ�
	Vec3 offset = { kCameraOffsetX, kCameraOffsetY, kCameraOffsetZ };

	// �J�����̈ʒu���v���C���[�̈ʒu�ɍ��킹��
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	// �v���C���[�̈ʒu�𒍎��_�ɂ���
	m_lookAtPos = { playerPos.x, playerPos.y + 150.0f, playerPos.z };

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}
