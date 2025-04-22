#include "ResultScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include "Input.h"
#include "game.h"
#include "DxLib.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cassert>
#include <cmath>

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
		int width = GetDrawStringWidthToHandle("RANK:S", strlen("RANK:S"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 50,
			"RANK:S", 0xffedab, m_fontHandle);
		width = GetDrawStringWidthToHandle(("Score:" + std::to_string(m_score)).c_str(),
			strlen(("Score:" + std::to_string(m_score)).c_str()), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2),
			("Score:" + std::to_string(m_score)).c_str(), 0xffedab, m_fontHandle);
	}
	else if (m_score >= 20000)
	{
		int width = GetDrawStringWidthToHandle("RANK:A", strlen("RANK:A"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 50,
			"RANK:A", 0xcc0033, m_fontHandle);
		width = GetDrawStringWidthToHandle(("Score:" + std::to_string(m_score)).c_str(),
			strlen(("Score:" + std::to_string(m_score)).c_str()), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2),
			("Score:" + std::to_string(m_score)).c_str(), 0xcc0033, m_fontHandle);
	}
	else if (m_score >= 15000)
	{
		int width = GetDrawStringWidthToHandle("RANK:B", strlen("RANK:B"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 50,
			"RANK:B", 0x00ccff, m_fontHandle);
		width = GetDrawStringWidthToHandle(("Score:" + std::to_string(m_score)).c_str(),
			strlen(("Score:" + std::to_string(m_score)).c_str()), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2),
			("Score:" + std::to_string(m_score)).c_str(), 0x00ccff, m_fontHandle);
	}
	else if (m_score >= 10000)
	{
		int width = GetDrawStringWidthToHandle("RANK:C", strlen("RANK:C"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 50,
			"RANK:C", 0x99ff99, m_fontHandle);
		width = GetDrawStringWidthToHandle(("Score:" + std::to_string(m_score)).c_str(),
			strlen(("Score:" + std::to_string(m_score)).c_str()), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2),
			("Score:" + std::to_string(m_score)).c_str(), 0x99ff99, m_fontHandle);
	}
	else
	{
		int width = GetDrawStringWidthToHandle("RANK:D", strlen("RANK:D"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 50,
			"RANK:D", 0x7a4171, m_fontHandle);
		width = GetDrawStringWidthToHandle(("Score:" + std::to_string(m_score)).c_str(),
			strlen(("Score:" + std::to_string(m_score)).c_str()), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2),
			("Score:" + std::to_string(m_score)).c_str(), 0x7a4171, m_fontHandle);
	}

	int width = GetDrawStringWidthToHandle(("TIME:" + std::to_string(m_time)).c_str(),
		strlen(("TIME:" + std::to_string(m_time)).c_str()), m_fontHandle);
	DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 100,
		("TIME:" + std::to_string(m_time)).c_str(), 0xffffff, m_fontHandle);
}

void ResultScene::FadeDraw()
{
}
