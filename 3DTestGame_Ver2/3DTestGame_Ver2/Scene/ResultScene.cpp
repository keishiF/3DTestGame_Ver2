#include "ResultScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include "Input.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	constexpr float kFadeInterval = 60;
}

ResultScene::ResultScene(SceneController& controller, int time, int score):
	SceneBase(controller),
	m_fadeFrame(0),
	m_blinkFrame(0),
	m_time(time),
	m_score(score),
	m_fontHandle(-1),
	m_update(&ResultScene::FadeInUpdate),
	m_draw(&ResultScene::FadeDraw)
{
	m_fontHandle = CreateFontToHandle("Algerian", 48, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	assert(m_fontHandle != -1);
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

		// Ž©•ª‚ªŽ€‚ñ‚Å‚¢‚é‚Ì‚Å‚à‚µ—]Œv‚Èˆ—‚ª“ü‚Á‚Ä‚¢‚é‚Æ‚Ü‚¸‚¢‚Ì‚Åreturn;
		return;
	}
}

void ResultScene::NormalDraw()
{
	if (m_score >= 30000)
	{
		DrawFormatStringToHandle(458, 400, 0xfdeff2, m_fontHandle, "Rank:");
		DrawFormatStringToHandle(655, 400, 0xffedab, m_fontHandle, "S");
		DrawFormatStringToHandle(435, 400, 0xfdeff2, m_fontHandle, "\nScore:");
		DrawFormatStringToHandle(650, 400, 0xffedab, m_fontHandle, "\n%d", m_score);
	}
	else if (m_score >= 20000)
	{
		DrawFormatStringToHandle(458, 400, 0xfdeff2, m_fontHandle, "Rank:");
		DrawFormatStringToHandle(655, 400, 0xcc0033, m_fontHandle, "A");
		DrawFormatStringToHandle(435, 400, 0xfdeff2, m_fontHandle, "\nScore:");
		DrawFormatStringToHandle(650, 400, 0xcc0033, m_fontHandle, "\n%d", m_score);
	}
	else if (m_score >= 15000)
	{
		DrawFormatStringToHandle(458, 400, 0xfdeff2, m_fontHandle, "Rank:");
		DrawFormatStringToHandle(655, 400, 0x00ccff, m_fontHandle, "B");
		DrawFormatStringToHandle(435, 400, 0xfdeff2, m_fontHandle, "\nScore:");
		DrawFormatStringToHandle(650, 400, 0x00ccff, m_fontHandle, "\n%d", m_score);
	}
	else if (m_score >= 10000)
	{
		DrawFormatStringToHandle(458, 400, 0xfdeff2, m_fontHandle, "Rank:");
		DrawFormatStringToHandle(655, 400, 0x99ff99, m_fontHandle, "C");
		DrawFormatStringToHandle(435, 400, 0xfdeff2, m_fontHandle, "\nScore:");
		DrawFormatStringToHandle(650, 400, 0x99ff99, m_fontHandle, "\n%d", m_score);
	}
	else
	{
		DrawFormatStringToHandle(458, 400, 0xfdeff2, m_fontHandle, "Rank:");
		DrawFormatStringToHandle(655, 400, 0x99ff99, m_fontHandle, "D");
		DrawFormatStringToHandle(435, 400, 0xfdeff2, m_fontHandle, "\nScore:");
		DrawFormatStringToHandle(650, 400, 0x99ff99, m_fontHandle, "\n%d", m_score);
	}

	DrawFormatStringToHandle(640, 100, 0xffffff, m_fontHandle, "Time\n%d", m_time);
}

void ResultScene::FadeDraw()
{
}
