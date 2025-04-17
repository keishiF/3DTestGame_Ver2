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

	// XV
	void Update(std::shared_ptr<Player> player);
	// •`‰æ
	void Draw();

	// “G‚ÌˆÊ’u‚ğæ“¾
	Vec3 GetPos() const { return m_pos; }
	// “G‚Ì“–‚½‚è”»’è‚ÌˆÊ’u‚ğæ“¾
	Vec3 GetColPos() const;
	// “G‚Ì”¼Œa‚ğæ“¾
	float GetRadius() const;
	// “G‚ğˆê’è”ÍˆÍ‚æ‚èŠO‘¤‚Éƒ‰ƒ“ƒ_ƒ€‚Å¶¬‚·‚é‚½‚ß‚ÌŠÖ”
	Vec3 GeneratePos(std::shared_ptr<Player> player);

private:
	// “G‚Ìƒ‚ƒfƒ‹
	int m_model;
	// “G‚ÌˆÊ’u
	Vec3 m_pos;
	Vec3 m_moveVec;

	void IdleUpdate(std::shared_ptr<Player> player);
	void RunUpdate(std::shared_ptr<Player> player);
	void DeadUpdate(std::shared_ptr<Player> player);

	// ó‘Ô‘JˆÚ‚Ì‚½‚ß‚Ì•Ï”
	using UpdateFunc_t = void (Enemy::*)(std::shared_ptr<Player> player);
	// ó‘Ô‚É‡‚í‚¹‚½ƒƒ“ƒoŠÖ”ƒ|ƒCƒ“ƒ^
	UpdateFunc_t m_update;
};

