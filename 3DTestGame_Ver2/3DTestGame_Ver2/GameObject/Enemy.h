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

	// 更新、描画
	void Update(std::shared_ptr<Player> player);
	void Draw();

	// エネミーの位置を取得
	Vec3 GetPos() const { return m_pos; }
	// エネミーの半径を取得
	float GetRadius() const { return m_radius; }

private:
	// エネミーの位置
	Vec3 m_pos;
	// 球の半径
	float m_radius;
};

