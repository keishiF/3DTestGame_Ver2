#pragma once
#include "Vec3.h"
#include "DxLib.h"
#include <memory>

class Player;
class Enemy
{
public:
	Enemy();
	~Enemy();

	// 更新
	void Update(std::shared_ptr<Player> player);
	// 描画
	void Draw();

	// 敵の位置を取得
	Vec3 GetPos() const { return m_pos; }
	// 敵の当たり判定の位置を取得
	Vec3 GetColPos() const;
	// 敵の半径を取得
	float GetRadius() const;
	// 敵を一定範囲より外側にランダムで生成するための関数
	Vec3 GeneratePos();

private:
	// 敵のモデル
	int m_model;
	// 敵の位置
	Vec3 m_pos;
	Vec3 m_moveVec;
	// 敵のスピード
	float m_speed;
	// フレーム数
	int m_frame;

	void IdleUpdate(std::shared_ptr<Player> player);
	void RunUpdate(std::shared_ptr<Player> player);
	void DeadUpdate(std::shared_ptr<Player> player);

	// 状態遷移のための変数
	using UpdateFunc_t = void (Enemy::*)(std::shared_ptr<Player> player);
	// 状態に合わせたメンバ関数ポインタ
	UpdateFunc_t m_update;
};

