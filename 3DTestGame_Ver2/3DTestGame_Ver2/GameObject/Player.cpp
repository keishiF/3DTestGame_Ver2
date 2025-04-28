#include "Player.h"
#include "Camera.h"
#include <cassert>

namespace
{
	// HP�̏����l
	constexpr int kHp = 100;
	// �ړ����x
	constexpr float kSpeed = 7.5f;
	// ���񑬓x
	constexpr float kRotSpeed = 0.05f;
	// �W�����v��
	constexpr float kJumpSpeed = 20.0f;
	// �d��
	constexpr float kGravity = 0.75f;

	// �v���C���[�̓����蔻��p�̋��̔��a
	constexpr float kColRadius = 90.0f;

	// �v���C���[�̈ړ��͈͂̐���
	constexpr float kMoveMin = -750.0f;
	constexpr float kMoveMax =  750.0f;
}

Player::Player() :
	m_model(-1),
	m_jumpSE(-1),
	m_anim(-1),
	m_pos(0.0f, 0.0f, 0.0f),
	m_vec(0.0f, 0.0f, 0.0f),
	m_angle(0.0f),
	m_rotMtx(MGetIdent()),
	m_hp(kHp),
	m_isLockOn(false),
	m_isJump(false),
	m_jumpSpeed(kJumpSpeed),
	m_gravity(kGravity),
	m_frameCount(0.0f)
{
	m_model = MV1LoadModel("Data/Model/Player/Player.mv1");
	assert(m_model != -1);
	m_anim = MV1AttachAnim(m_model, 3, -1, false);
	assert(m_anim != -1);
	m_jumpSE = LoadSoundMem("Data/Sound/SE/JumpSE2.mp3");
	assert(m_jumpSE != -1);

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
}

Player::~Player()
{
	MV1DetachAnim(m_model, m_anim);
	MV1DeleteModel(m_model);
	DeleteSoundMem(m_jumpSE);
}

void Player::Update(Input& input, std::shared_ptr<Camera> camera)
{
	// �A�j���[�V������i�߂�
	m_frameCount += 1.0f;

	// ���ݍĐ����̃A�j���[�V�����̑����Ԃ��擾����
	const float totalTime = MV1GetAttachAnimTotalTime(m_model, m_anim);

	MV1SetAttachAnimTime(m_model, m_anim, m_frameCount);

	if (!m_isLockOn)
	{
		if (input.IsTrigger(PAD_INPUT_6)) { m_isLockOn = true; }
	}
	else
	{
		if (input.IsTrigger(PAD_INPUT_6)) { m_isLockOn = false; }
	}

	// �J�����̉�]�s����擾
	float angle = camera->GetCamRotX();

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

	// �W�����v�J�n�̓��͏���
	if (input.IsTrigger(PAD_INPUT_1))
	{
		StartJump();
	}

	// �W�����v�̍X�V����
	UpdateJump();

	m_rotMtx = MGetRotY(angle);
	VECTOR vec = VTransform(VGet(m_vec.x, m_vec.y, m_vec.z), m_rotMtx);
	m_pos.x += vec.x;
	m_pos.y += vec.y;
	m_pos.z += vec.z;

	if (m_pos.x < kMoveMin) { m_pos.x = kMoveMin; }
	if (m_pos.x > kMoveMax) { m_pos.x = kMoveMax; }
	if (m_pos.z < kMoveMin) { m_pos.z = kMoveMin; }
	if (m_pos.z > kMoveMax) { m_pos.z = kMoveMax; }

	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	MV1SetRotationXYZ(m_model, VGet(0.0f, m_angle, 0.0f));
}

void Player::Draw()
{
	MV1DrawModel(m_model);

#ifdef _DEBUG
	DrawSphere3D(VGet(m_pos.x, m_pos.y, m_pos.z), 20.0f, 16, 0x0000ff, 0x0000ff, true);
	DrawSphere3D(VGet(GetColPos().x, GetColPos().y, GetColPos().z), kColRadius, 16, 0xff00ff, 0xff00ff, false);
#endif
}

void Player::OnDamage()
{
	m_hp--;
}

float Player::GetRadius() const
{
	return kColRadius;
}

Vec3 Player::GetColPos() const
{
	Vec3 result = m_pos;
	result.y += 80.0f;
	return result;
}

void Player::StartJump()
{
	// �W�����v���łȂ��ꍇ�̂݃W�����v���J�n
	if (!m_isJump)
	{
		m_isJump = true;
		m_jumpSpeed = kJumpSpeed;
		PlaySoundMem(m_jumpSE, DX_PLAYTYPE_BACK);
	}
}

void Player::UpdateJump()
{
	if (m_isJump)
	{
		// �W�����v���̏���
		m_pos.y += m_jumpSpeed;
		m_jumpSpeed -= m_gravity;

		// �n�ʂɖ߂�����W�����v�I��
		if (m_pos.y <= 0.0f)
		{
			m_pos.y = 0.0f;
			m_isJump = false;
			m_jumpSpeed = 0.0f;
		}
	}
}

