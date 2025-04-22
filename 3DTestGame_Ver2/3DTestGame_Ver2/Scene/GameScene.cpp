#include "GameScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "SceneController.h"
#include "game.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "ColliderManager.h"
#include <cassert>

namespace
{
	constexpr int kFadeInterval = 60;
	// フィールドの一辺の長さ
	constexpr float kFieldSize = 750.0f;
	// スカイドームのモデルの拡大率
	constexpr float kSkyScale = 5.0f;
	// 地面のモデルの拡大率
	constexpr float kFieldScale = 9.0f;
}

GameScene::GameScene(SceneController& controller) :
	SceneBase(controller),
	m_frame(0),
	m_timeSecond(3),
	m_timeFrame(0),
	m_fadeFrame(0),
	m_skyModel(-1),
	m_skyPos(0.0f, 0.0f, 0.0f),
	m_fieldModel(-1),
	m_fontHandle(-1),
	m_hitPolyDim(),
	m_isHitPoly(false),
	m_update(&GameScene::FadeInUpdate),
	m_draw(&GameScene::FadeDraw)
{
	m_skyModel = MV1LoadModel("Data/Model/Sky/Sky_Daylight01.mv1");
	assert(m_skyModel != -1);
	m_fieldModel = MV1LoadModel("Data/Model/Field/Field.mv1");
	assert(m_fieldModel != -1);
	m_fontHandle = CreateFontToHandle("Algerian", 48, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	assert(m_fontHandle != -1);

	m_player = std::make_shared<Player>();
	m_enemy = std::make_shared<Enemy>();
	m_camera = std::make_shared<Camera>();
	m_camera->SetCamera(m_player);

	// スカイドームの設定
	MV1SetScale(m_skyModel, VGet(kSkyScale, kSkyScale, kSkyScale));
	MV1SetPosition(m_skyModel, VGet(m_skyPos.x, m_skyPos.y, m_skyPos.z));

	// 地面の設定
	MV1SetScale(m_fieldModel, VGet(kFieldScale, kFieldScale, kFieldScale));
	MV1SetPosition(m_fieldModel, VGet(0.0f, -890.0f, 0.0f));
}

GameScene::~GameScene()
{
	MV1DeleteModel(m_skyModel);
	MV1DeleteModel(m_fieldModel);
}

void GameScene::Update(Input& input)
{
	(this->*m_update)(input);
}

void GameScene::Draw()
{
	(this->*m_draw)();
}

void GameScene::CountDown(Input& input)
{
	++m_frame;
	if (m_timeSecond <= 0 && m_frame >= 60)
	{
		m_frame = 0;
		m_update = &GameScene::NormalUpdate;
		m_draw = &GameScene::NormalDraw;
	}
	if (m_frame >= 60)
	{
		m_frame = 0;
		m_timeSecond -= 1;
	}
}

void GameScene::NormalUpdate(Input& input)
{
	++m_frame;

	++m_timeFrame;
	if (m_timeFrame >= 60)
	{
		m_timeSecond += 1;
		m_timeFrame = 0;
	}

	m_enemy->Update(m_player);
	m_player->Update(input, m_camera);
	m_camera->Update(m_player, m_enemy);

	// プレイヤーと敵の当たり判定
	if (m_colliderManager->SphereToSphere(m_player->GetColPos(), m_player->GetRadius(), m_enemy->GetColPos(), m_enemy->GetRadius()))
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
		m_update = &GameScene::CountDown;
		m_draw = &GameScene::CountDownDraw;
	}
}

void GameScene::FadeOutUpdate(Input&)
{
	if (m_fadeFrame++ >= kFadeInterval)
	{
		int score = 0;
		if (m_timeSecond >= 60)
		{
			score = 30000;
		}
		else if (m_timeSecond >= 45)
		{
			score = 20000;
		}
		else if (m_timeSecond >= 30)
		{
			score = 15000;
		}
		else if (m_timeSecond >= 15)
		{
			score = 10000;
		}
		else
		{
			score = 0;
		}

		m_controller.ChangeScene(std::make_shared<ResultScene>(m_controller, m_timeSecond, score));

		// 自分が死んでいるのでもし余計な処理が入っているとまずいのでreturn;
		return;
	}
}

void GameScene::CountDownDraw()
{
	MV1DrawModel(m_skyModel);

	DrawField();

	m_player->Draw();

	int width = GetDrawFormatStringWidthToHandle(m_fontHandle, "%d", m_timeSecond);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2 - 64 / 2,
		0xff0000, m_fontHandle, "%d", m_timeSecond);
}

void GameScene::NormalDraw()
{
	printf("frame %d　PlayerHP=%d　PlayerPos X=%f,Y=%f,Z=%f　EnemyPos X=%f,Y=%f,Z=%f\r", 
		m_frame,
		m_player->GetHp(),
		m_player->GetPos().x, m_player->GetPos().y, m_player->GetPos().z,
		m_enemy->GetPos().x, m_enemy->GetPos().y, m_enemy->GetPos().z);

	MV1DrawModel(m_skyModel);

	DrawField();

	m_player->Draw();
	m_enemy->Draw();

	int width = GetDrawStringWidthToHandle("TIME", strlen("TIME"), m_fontHandle);
	DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 320,
		"TIME", 0x7fffd4, m_fontHandle);
	width = GetDrawFormatStringWidthToHandle(m_fontHandle, "%d", m_timeSecond);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - width / 2, (Game::kScreenHeight / 2 - 64 / 2) - 275,
		0xff0000, m_fontHandle, "%d", m_timeSecond);
}

void GameScene::FadeDraw()
{
	float rate = static_cast<float>(m_fadeFrame) / static_cast<float>(kFadeInterval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::DrawField()
{
	MV1DrawModel(m_fieldModel);

	//// 1枚床
	//DrawTriangle3D(VGet(750.0f, 0.0f, -750.0f), VGet(-750.0f, 0.0f, -750.0f), VGet(750.0f, 0.0f, 750.0f), 0xffffff, true);
	//DrawTriangle3D(VGet(-750.0f, 0.0f, -750.0f), VGet(-750.0f, 0.0f, 750.0f), VGet(750.0f, 0.0f, 750.0f), 0xffffff, true);

	//// グリッド
	//Vec3 start;
	//Vec3 end;
	//start = { -kFieldSize, 0.0f,0.0f };
	//end = { kFieldSize, 0.0f,0.0f };
	//for (int z = -kFieldSize; z <= kFieldSize; z += 50)
	//{
	//	start.z = z;
	//	end.z = z;

	//	DrawLine3D(VGet(start.x, start.y, start.z), VGet(end.x, end.y, end.z), 0xff0000);
	//}
	//start = { 0.0f, 0.0f, -kFieldSize };
	//end = { 0.0f, 0.0f, kFieldSize };
	//for (int x = -kFieldSize; x <= kFieldSize; x += 50)
	//{
	//	start.x = x;
	//	end.x = x;

	//	DrawLine3D(VGet(start.x, start.y, start.z), VGet(end.x, end.y, end.z), 0x0000ff);
	//}
}
