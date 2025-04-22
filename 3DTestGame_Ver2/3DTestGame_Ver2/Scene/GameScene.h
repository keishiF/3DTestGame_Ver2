#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include "Vec3.h"
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
	int m_frame;
	int m_timeSecond;
	int m_timeFrame;
	int m_fadeFrame;

	int m_skyModel;
	Vec3 m_skyPos;

	int m_fieldModel;

	int m_fontHandle;

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

	// ゲーム開始前のカウントダウン
	void CountDown(Input& input);
	// 通常時更新処理
	void NormalUpdate(Input& input);
	// フェードイン
	void FadeInUpdate(Input&);
	// フェードアウト
	void FadeOutUpdate(Input&);

	// ゲーム開始前のカウントダウンの描画
	void CountDownDraw();
	// 通常時描画
	void NormalDraw();
	// フェード時の描画
	void FadeDraw();

	// グリッドを描画
	void DrawField();
};

