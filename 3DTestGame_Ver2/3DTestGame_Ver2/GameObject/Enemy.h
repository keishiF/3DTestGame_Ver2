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
	// �G�l�~�[�̈ʒu
	Vec3 m_pos;
	// �G�l�~�[��HP 
	int m_hp;
};

