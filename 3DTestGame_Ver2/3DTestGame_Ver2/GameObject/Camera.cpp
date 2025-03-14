#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <algorithm>

namespace
{
	constexpr float kLerpRate = 0.05f;
	constexpr float kRotSpeed = 0.00005f;
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
	Vec3 playerPos = player->GetPos();
	Vec3 enemyPos = enemy->GetPos();

	Vec3 offset = { 0.0f, 300.0f, 500.0f };

	m_pos = playerPos;

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	m_isLockOn = player->IsLockOn();

	int inputX, inputY;

	if (!m_isLockOn)
	{
		GetJoypadAnalogInputRight(&inputX, &inputY, DX_INPUT_PAD1);

		// カメラの回転をジョイパッドの入力に基づいて更新
		if (inputX != 0)
		{
			m_cameraRotX += inputX * kRotSpeed;
		}

		if (inputY != 0)
		{
			m_cameraRotY += inputY * kRotSpeed;
			// 縦回転に制限を付ける
			m_cameraRotY = std::clamp(m_cameraRotY, -DX_PI_F / 3.0f, DX_PI_F / 5.80f);
		}
	}

	printf("m_cameraRotY = %f　", m_cameraRotY);
	printf("a = %f, b = %f　", -DX_PI_F / 2.0f, DX_PI_F / 2.0f);

	if (m_isLockOn)
	{
		Vec3 targetPos = (playerPos + enemyPos) * 0.5f;
		targetPos.y += 150.0f;
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}
	else if (!m_isLockOn)
	{
		Vec3 targetPos = { playerPos.x, playerPos.y + 175.0f, playerPos.z - 150.0f };
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}

	// カメラの位置を回転に基づいて更新
	Vec3 rotatedOffset = {
		offset.x * cos(m_cameraRotX) - offset.z * sin(m_cameraRotX),
		offset.y * cos(m_cameraRotY) - offset.z * sin(m_cameraRotY),
		offset.x * sin(m_cameraRotX) + offset.z * cos(m_cameraRotX)
	};
	m_pos = playerPos + rotatedOffset;

	DrawSphere3D(VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z), 20.0f, 16, 0xffffff, 0xffffff, true);

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}

void Camera::SetCamera(std::shared_ptr<Player> player)
{
	Vec3 playerPos = player->GetPos();

	Vec3 offset = { 0.0f, 300.0f, 500.0f };

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	m_lookAtPos = { playerPos.x, playerPos.y + 150.0f, playerPos.z };

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}
