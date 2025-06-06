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
	// 更新処理
	void Update(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy);
	// カメラの初期化
	void SetCamera(std::shared_ptr<Player> player);

	// カメラの回転行列を取得
	float GetCamRotX() const { return m_cameraRotX; }
	float GetCamRotY() const { return m_cameraRotY; }

private:
	// カメラの位置
	Vec3 m_pos;
	// カメラの注視点
	Vec3 m_lookAtPos;
	// カメラの視野角
	float m_fov;
	// カメラの回転量
	float m_cameraRotX;
	float m_cameraRotY;
	// ロックオンフラグ
	bool m_isLockOn;
};

