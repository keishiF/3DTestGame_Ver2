#include "GameScene.h"
#include "TitleScene.h"
#include "SceneController.h"
#include "game.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include <cassert>

namespace
{
	constexpr int kFadeInterval = 60;
}

GameScene::GameScene(SceneController& controller) :
	SceneBase(controller),
	m_fadeFrame(0),
	m_blinkFrame(0),
	m_update(&GameScene::FadeInUpdate),
	m_draw(&GameScene::FadeDraw)
{
	m_player = std::make_shared<Player>();

	m_enemy = std::make_shared<Enemy>();

	m_camera = std::make_shared<Camera>();
	m_camera->SetCamera(m_player);
}

GameScene::~GameScene()
{

}

void GameScene::Update(Input& input)
{
	(this->*m_update)(input);
}

void GameScene::Draw()
{
	(this->*m_draw)();
}

void GameScene::NormalUpdate(Input& input)
{
	++m_blinkFrame;

	m_enemy->Update();
	m_player->Update(input, m_camera);
	m_camera->Update(m_player, m_enemy);

	if (input.IsPress(GetJoypadInputState(PAD_INPUT_1)))
	{
		m_update = &GameScene::FadeOutUpdate;
		m_draw = &GameScene::FadeDraw;
		m_fadeFrame = 0;
	}
}

void GameScene::FadeInUpdate(Input&)
{
	if (m_fadeFrame-- <= 0)
	{
		m_update = &GameScene::NormalUpdate;
		m_draw = &GameScene::NormalDraw;
	}
}

void GameScene::FadeOutUpdate(Input&)
{
	if (m_fadeFrame++ >= kFadeInterval)
	{
		m_controller.ChangeScene(std::make_shared<TitleScene>(m_controller));

		// ©•ª‚ª€‚ñ‚Å‚¢‚é‚Ì‚Å‚à‚µ—]Œv‚Èˆ—‚ª“ü‚Á‚Ä‚¢‚é‚Æ‚Ü‚¸‚¢‚Ì‚Åreturn;
		return;
	}
}

void GameScene::NormalDraw()
{
	//DrawString(0, 0, "Game Scene", 0xffffff);

	Vec3 start;
	Vec3 end;
	start = { -1000.0f, 0.0f,0.0f };
	end = { 1000.0f, 0.0f,0.0f };
	for (int z = -1000; z <= 1000; z += 100)
	{
		start.z = z;
		end.z = z;

		DrawLine3D(VGet(start.x, start.y, start.z), VGet(end.x, end.y, end.z), 0xff0000);
	}
	start = { 0.0f, 0.0f, -1000.0f };
	end = { 0.0f, 0.0f, 1000.0f };
	for (int x = -1000; x <= 1000; x += 100)
	{
		start.x = x;
		end.x = x;

		DrawLine3D(VGet(start.x, start.y, start.z), VGet(end.x, end.y, end.z), 0x0000ff);
	}

	m_player->Draw();
	m_enemy->Draw();

	// “_–ÅŒø‰Ê‚Ì‚½‚ß‚ÌğŒ
	if ((m_blinkFrame / 30) % 2 == 0)
	{

	}
}

void GameScene::FadeDraw()
{
	float rate = static_cast<float>(m_fadeFrame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
