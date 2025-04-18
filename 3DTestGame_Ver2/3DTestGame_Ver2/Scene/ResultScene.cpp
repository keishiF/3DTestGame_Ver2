#include "ResultScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include "Input.h"
#include "DxLib.h"

namespace
{
	constexpr float kFadeInterval = 60;
}

ResultScene::ResultScene(SceneController& controller):
	SceneBase(controller),
	m_fadeFrame(0),
	m_blinkFrame(0),
	m_update(&ResultScene::FadeInUpdate),
	m_draw(&ResultScene::FadeDraw)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update(Input& input)
{
	(this->*m_update)(input);
}

void ResultScene::Draw()
{
	(this->*m_draw)();
}

void ResultScene::NormalUpdate(Input& input)
{
	++m_blinkFrame;

	if (input.IsPress(CheckHitKeyAll()))
	{
		m_update = &ResultScene::FadeOutUpdate;
		m_draw = &ResultScene::FadeDraw;
		m_fadeFrame = 0;
	}
}

void ResultScene::FadeInUpdate(Input&)
{
	if (m_fadeFrame-- <= 0)
	{
		m_update = &ResultScene::NormalUpdate;
		m_draw = &ResultScene::NormalDraw;
	}
}

void ResultScene::FadeOutUpdate(Input&)
{
	if (m_fadeFrame++ >= kFadeInterval)
	{
		m_controller.ChangeScene(std::make_shared<TitleScene>(m_controller));

		// ©•ª‚ª€‚ñ‚Å‚¢‚é‚Ì‚Å‚à‚µ—]Œv‚Èˆ—‚ª“ü‚Á‚Ä‚¢‚é‚Æ‚Ü‚¸‚¢‚Ì‚Åreturn;
		return;
	}
}

void ResultScene::NormalDraw()
{
	// “_–ÅŒø‰Ê‚Ì‚½‚ß‚ÌğŒ
	if ((m_blinkFrame / 30) % 2 == 0)
	{
		DrawString(0, 0, "Result Scene", 0xffffff);
	}
}

void ResultScene::FadeDraw()
{
}
