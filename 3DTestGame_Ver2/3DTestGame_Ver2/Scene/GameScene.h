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

	// �Q�[���J�n�O�̃J�E���g�_�E��
	void CountDown(Input& input);
	// �ʏ펞�X�V����
	void NormalUpdate(Input& input);
	// �t�F�[�h�C��
	void FadeInUpdate(Input&);
	// �t�F�[�h�A�E�g
	void FadeOutUpdate(Input&);

	// �Q�[���J�n�O�̃J�E���g�_�E���̕`��
	void CountDownDraw();
	// �ʏ펞�`��
	void NormalDraw();
	// �t�F�[�h���̕`��
	void FadeDraw();

	// �O���b�h��`��
	void DrawField();
};

