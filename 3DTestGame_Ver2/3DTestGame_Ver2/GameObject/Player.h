#pragma once

#include "DxLib.h"
#include "Input.h"
#include "Vec3.h"
#include <memory>

class Camera;
class Player
{
public:
	// コンストラクタとデストラクタ
	Player();
	virtual ~Player();

	// 更新、描画
	void Update(Input& input, std::shared_ptr<Camera> camera);
	void Draw();

	// ダメージを受けた時の処理をまとめる関数
	void OnDamage();

	// 位置の取得
	Vec3 GetPos() const { return m_pos; }
	// 回転行列の取得
	MATRIX GetRotMtx() const { return m_rotMtx; }
	// ロックオンしているかの取得
	bool IsLockOn() const { return m_isLockOn; }

private:
	// ジャンプ関連の関数
	void StartJump();
	void UpdateJump();

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
	// ジャンプ状態
	bool m_isJump;
	float m_jumpSpeed;
	float m_gravity;

	// 経過フレームを測る
	float m_frameCount;
};

