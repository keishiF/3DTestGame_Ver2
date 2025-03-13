#pragma once
#include "Vec3.h"
#include "DxLib.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update();
	void Draw();

	void Ondamage();

	Vec3 GetPos() const { return m_pos; }

private:
	// エネミーの位置
	Vec3 m_pos;
	// エネミーのHP 
	int m_hp;
};

