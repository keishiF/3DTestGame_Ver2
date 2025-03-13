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
	// プレイヤーのモデル
	int m_model;
	// アニメーションハンドル
	int m_anim;
	// プレイヤーの位置
	Vec3 m_pos;
	// プレイヤーの移動量
	Vec3 m_vec;
	// プレイヤーの向いている方向
	float m_angle;
	// プレイヤーの回転行列
	MATRIX m_rotMtx;
	// プレイヤーのHP
	int m_hp;
	// ロックオンフラグ
	bool m_isLockOn;
	// ジャンプ
	bool m_isJump;

	// 経過フレームを測る
	float m_frameCount;
};

