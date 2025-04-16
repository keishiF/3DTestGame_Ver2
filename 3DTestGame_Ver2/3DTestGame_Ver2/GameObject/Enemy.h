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

	// XVA•`‰æ
	void Update(std::shared_ptr<Player> player);
	void Draw();

	// “G‚ÌˆÊ’u‚ğæ“¾
	Vec3 GetPos() const { return m_pos; }
	// “G‚Ì“–‚½‚è”»’è‚ÌˆÊ’u‚ğæ“¾
	Vec3 GetColPos() const;
	// “G‚Ì”¼Œa‚ğæ“¾
	float GetRadius() const;

private:
	// “G‚Ìƒ‚ƒfƒ‹
	int m_model;
	// “G‚ÌˆÊ’u
	Vec3 m_pos;
};

