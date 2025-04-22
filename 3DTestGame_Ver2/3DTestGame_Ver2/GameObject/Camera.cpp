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
	// プレイヤーとエネミーの位置を取得
	Vec3 playerPos = player->GetPos();
	Vec3 enemyPos = enemy->GetPos();

	// カメラの位置を補正する値の設定
	Vec3 offset = { kCameraOffsetX, kCameraOffsetY, kCameraOffsetZ };

	// カメラの位置をプレイヤーの位置に基づいて更新
	m_pos = playerPos;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	// ロックオンしているかどうか
	m_isLockOn = player->IsLockOn();

	int inputX, inputY;

	//// ロックオンしていないときだけカメラを回転できるようにする
	//if (!m_isLockOn)
	//{
	//	// 右スティックの入力を取得
	//	GetJoypadAnalogInputRight(&inputX, &inputY, DX_INPUT_PAD1);

	//	// カメラの回転をジョイパッドの入力に基づいて更新
	//	if (inputX != 0)
	//	{
	//		m_cameraRotX += inputX * kRotSpeed;
	//	}

	//	if (inputY != 0)
	//	{
	//		m_cameraRotY += inputY * kRotSpeed;
	//		// 縦回転に制限を付ける
	//		m_cameraRotY = std::clamp(m_cameraRotY, -DX_PI_F / 3.0f, DX_PI_F / 5.80f);
	//	}
	//}

	// ロックオンしている時は
	// プレイヤーとエネミーの中間地点を注視点にする
	if (m_isLockOn)
	{
		Vec3 targetPos = (playerPos + enemyPos) * 0.5f;
		targetPos.y += 150.0f;
		m_lookAtPos = Vec3::Lerp(m_lookAtPos, targetPos, kLerpRate);
	}
	// ロックオンしていない時は
	// プレイヤーの位置を注視点にする
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

#ifdef _DEBUG
	DrawSphere3D(VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z), 20.0f, 16, 0xffffff, 0xffffff, true);
#endif

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}

void Camera::SetCamera(std::shared_ptr<Player> player)
{
	// プレイヤーの位置を取得
	Vec3 playerPos = player->GetPos();

	// カメラの位置を補正する値の設定
	Vec3 offset = { kCameraOffsetX, kCameraOffsetY, kCameraOffsetZ };

	// カメラの位置をプレイヤーの位置に合わせる
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pos = playerPos + offset;

	// プレイヤーの位置を注視点にする
	m_lookAtPos = { playerPos.x, playerPos.y + 150.0f, playerPos.z };

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_pos.x, m_pos.y, m_pos.z),
		VGet(m_lookAtPos.x, m_lookAtPos.y, m_lookAtPos.z));
}
