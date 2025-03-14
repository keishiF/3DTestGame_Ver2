#include "Player.h"
#include "Camera.h"
#include <cassert>

namespace
{
	// HPの初期値
	constexpr int kHp = 5;
	// 移動速度
	constexpr float kSpeed = 7.5f;
	// 旋回速度
	constexpr float kRotSpeed = 0.05f;
}

Player::Player() :
	m_model(-1),
	m_anim(-1),
	m_pos(0.0f, 0.0f, 0.0f),
	m_vec(0.0f, 0.0f, 0.0f),
	m_angle(0.0f),
	m_rotMtx(MGetIdent()),
	m_hp(kHp),
	m_isLockOn(false),
	m_isJump(false),
	m_frameCount(0.0f)
{
	m_model = MV1LoadModel("Data/Model/Player.mv1");
	assert(m_model != -1);
	m_anim = MV1AttachAnim(m_model, 3, -1, false);
	assert(m_anim != -1);

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

Player::~Player()
{
	MV1DetachAnim(m_model, m_anim);
	MV1DeleteModel(m_model);
}

void Player::Update(Input& input, std::shared_ptr<Camera> camera)
{
	// アニメーションを進める
	m_frameCount += 1.0f;

	// 現在再生中のアニメーションの総時間を取得する
	const float totalTime = MV1GetAttachAnimTotalTime(m_model, m_anim);

	// アニメーションの設定によってループさせるか最後のフレームで止めるかを判定
	while (m_frameCount > totalTime)
	{
		if (!m_isJump)
		{
			m_frameCount -= totalTime;
		}
		else
		{

		}
	}

	MV1SetAttachAnimTime(m_model, m_anim, m_frameCount);

	if (!m_isLockOn)
	{
		if (input.IsTrigger(PAD_INPUT_6)) { m_isLockOn = true; }
	}
	else
	{
		if (input.IsTrigger(PAD_INPUT_6)) { m_isLockOn = false; }
	}

	// カメラの回転行列を取得
	float angle = camera->GetCamRot();

	if (input.IsPress(PAD_INPUT_LEFT))
	{
		m_vec.x = kSpeed;
	}
	else if (input.IsPress(PAD_INPUT_RIGHT))
	{
		m_vec.x = -kSpeed;
	}
	else
	{
		m_vec.x = 0.0f;
	}

	if (input.IsPress(PAD_INPUT_UP))
	{
		m_vec.z = -kSpeed;
	}
	else if (input.IsPress(PAD_INPUT_DOWN))
	{
		m_vec.z = kSpeed;
	}
	else
	{
		m_vec.z = 0.0f;
	}

	m_rotMtx = MGetRotY(angle);
	VECTOR vec = VTransform(VGet(m_vec.x, m_vec.y, m_vec.z), m_rotMtx);
	m_pos.x += vec.x;
	m_pos.y += vec.y;
	m_pos.z += vec.z;

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	MV1SetRotationXYZ(m_model, VGet(0.0f, m_angle, 0.0f));
}

void Player::Draw()
{
	printf("PlayerPos：X=%f,Y=%f,Z=%f　\r", m_pos.x, m_pos.y, m_pos.z);
	MV1DrawModel(m_model);
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), 20.0f, 16, 0x0000ff, 0x0000ff, true);
}

void Player::OnDamage()
{
	m_hp--;
}
