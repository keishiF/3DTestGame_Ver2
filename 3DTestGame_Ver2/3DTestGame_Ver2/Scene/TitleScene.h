#pragma once
#include "SceneBase.h"
#include "Vec3.h"

class TitleScene final:
	public SceneBase
{
public:
	TitleScene(SceneController& controller);
	~TitleScene();

	virtual void Update(Input& input) override;
	virtual void Draw() override;

private:
	int m_fadeFrame;
	int m_blinkFrame;

	int m_fontHandle;
	int m_titleBGHandle;
	int m_skyModel;

	Vec3 m_cameraPos;
	Vec3 m_cameraLookAt;
	float m_cameraAngle;

	using UpdateFunc_t = void(TitleScene::*)(Input&);
	using DrawFunc_t = void(TitleScene::*)();

	UpdateFunc_t m_update;
	DrawFunc_t m_draw;

	// �ʏ펞�X�V����
	void NormalUpdate(Input& input);
	// �t�F�[�h�C��
	void FadeInUpdate(Input&);
	// �t�F�[�h�A�E�g
	void FadeOutUpdate(Input&);

	// �ʏ펞�`��
	void NormalDraw();
	// �t�F�[�h���̕`��
	void FadeDraw();
};

