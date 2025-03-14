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
	// カメラの位置
	Vec3 m_pos;
	// カメラの注視点
	Vec3 m_lookAtPos;
	// カメラの視野角
	float m_fov;
	// カメラの回転量
	float m_cameraRot;
	// ロックオンフラグ
	bool m_isLockOn;
};

