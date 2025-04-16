#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include "Vector3.h"
#include <memory>

class Player;
class Enemy;
class Camera;
class ColliderManager;
class GameScene final:
	public SceneBase
{
public:
	GameScene(SceneController& controller);
	~GameScene();

	virtual void Update(Input& input) override;
	virtual void Draw() override;

private:
	int m_frameCount;

	int m_fadeFrame;

	int m_blinkFrame;

	int m_skyModel;
	Vector3 m_skyPos;

	MV1_COLL_RESULT_POLY_DIM m_hitPolyDim;
	bool m_isHitPoly;

	using UpdateFunc_t = void(GameScene::*)(Input&);
	using DrawFunc_t = void(GameScene::*)();

	UpdateFunc_t m_update;
	DrawFunc_t m_draw;

	std::shared_ptr<Player> m_player;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Enemy> m_enemy;
	std::shared_ptr<ColliderManager> m_colliderManager;

	// 通常時更新処理
	void NormalUpdate(Input& input);
	// フェードイン
	void FadeInUpdate(Input&);
	// フェードアウト
	void FadeOutUpdate(Input&);

	// 通常時描画
	void NormalDraw();
	// フェード時の描画
	void FadeDraw();
};

