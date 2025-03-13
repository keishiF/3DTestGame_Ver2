#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>

namespace
{
	constexpr float kLerpRate = 0.05f;

	constexpr VECTOR kOffset{ 0.0f, 300.0f, 500.0f };
	constexpr VECTOR kTarget{ 0.0f, 150.0f, 0.0f };
}

Camera::Camera() :
	m_pos(0.0f, 0.0f, 0.0f),
	m_lookAtPos(0.0f, 0.0f, 0.0f),
	m_fov(DX_PI_F / 3.0f),
	m_cameraRot(0.0f),
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

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	m_isLockOn = player->IsLockOn();

	if (m_isLockOn)
	{
		Vec3 targetPos = (playerPos + enemyPos) * 0.5f;
		targetPos.y += 150.0f;
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}
	else if (!m_isLockOn)
	{
		Vec3 targetPos = { playerPos.x, playerPos.y + 150.0f, playerPos.z };
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}

void Camera::SetCamera(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)
{
	Vec3 playerPos = player->GetPos();
	Vec3 enemyPos = enemy->GetPos();

	Vec3 offset = { 0.0f, 300.0f, 500.0f };

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	m_lookAtPos = { playerPos.x, playerPos.y + 150.0f, playerPos.z };

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}
