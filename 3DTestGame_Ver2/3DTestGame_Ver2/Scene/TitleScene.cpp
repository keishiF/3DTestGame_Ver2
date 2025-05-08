#include "TitleScene.h"
#include "GameScene.h"
#include "SceneController.h"
#include "game.h"
#include "Input.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	constexpr int kFadeInterval = 60;
}

TitleScene::TitleScene(SceneController& controller) :
	SceneBase(controller),
	m_fadeFrame(kFadeInterval),
	m_blinkFrame(0),
	m_titleBGHandle(-1),
	m_skyModel(-1),
	m_cameraPos(0.0f, 200.0f, -500.0f),
	m_cameraLookAt(0.0f, 0.0f, 0.0f),
	m_cameraAngle(0.0f), 
	m_update(&TitleScene::FadeInUpdate),
	m_draw(&TitleScene::FadeDraw)
{
	m_titleBGHandle = LoadGraph("Data/Image/Title.png");
	assert(m_titleBGHandle != -1);

	m_skyModel = MV1LoadModel("Data/Model/Sky/Sky_Daylight01.mv1");
	assert(m_skyModel != -1);

	m_fontHandle = CreateFontToHandle("Algerian", 48, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	assert(m_fontHandle != -1);
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_titleBGHandle);
	MV1DeleteModel(m_skyModel);
}

void TitleScene::Update(Input& input)
{
	(this->*m_update)(input);
}

void TitleScene::Draw()
{
	(this->*m_draw)();
}

void TitleScene::NormalUpdate(Input& input)
{
	++m_blinkFrame;

	// カメラの回転処理
	m_cameraAngle += 0.001f; // 回転速度
	m_cameraPos.x = 500.0f * cosf(m_cameraAngle);
	m_cameraPos.z = 500.0f * sinf(m_cameraAngle);

	SetCameraPositionAndTarget_UpVecY(
		VGet(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z),
		VGet(m_cameraLookAt.x, m_cameraLookAt.y, m_cameraLookAt.z)
	);

	if (input.IsPress(CheckHitKeyAll()))
	{
		m_update = &TitleScene::FadeOutUpdate;
		m_draw = &TitleScene::FadeDraw;
		m_fadeFrame = 0;
	}
}

void TitleScene::FadeInUpdate(Input&)
{
	if (m_fadeFrame-- <= 0)
	{
		m_update = &TitleScene::NormalUpdate;
		m_draw = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	if (m_fadeFrame++ >= kFadeInterval)
	{
		m_controller.ChangeScene(std::make_shared<GameScene>(m_controller));

		// 自分が死んでいるのでもし余計な処理が入っているとまずいのでreturn;
		return;
	}
}

void TitleScene::NormalDraw()
{
	MV1DrawModel(m_skyModel);
	DrawGraph(0, 0, m_titleBGHandle, true);

	// 点滅効果のための条件
	if ((m_blinkFrame / 30) % 2 == 0)
	{
		int width = GetDrawStringWidthToHandle("PRESS ANY BUTTON", strlen("PRESS ANY BUTTON"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, ((Game::kScreenHeight / 2 - 64 / 2) - 50) + 150,
			"PRESS ANY BUTTON", 0xff7fff, m_fontHandle);
		width = GetDrawStringWidthToHandle("START", strlen("START"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, ((Game::kScreenHeight / 2 - 64 / 2) - 50) + 150,
			"\nSTART", 0xff7fff, m_fontHandle);
	}
}

void TitleScene::FadeDraw()
{
	float rate = static_cast<float>(m_fadeFrame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
