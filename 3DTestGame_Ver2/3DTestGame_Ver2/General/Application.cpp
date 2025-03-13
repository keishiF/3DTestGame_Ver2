#include "Application.h"
#include "SceneController.h"
#include "Input.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>

Application& Application::GetInstance()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	static Application app;
	return app;
}

bool Application::Init()
{
	// �t���X�N���[���ł͂Ȃ��A�E�C���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);
	// �E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʂ̃T�C�Y��ύX����
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBItNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return false;			// �G���[���N�����璼���ɏI��
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Application::Run()
{
	m_frame = 0;

	// �������̊m��
	SceneController sceneController;
	Input input;

	// �Q�[�����[�v
	while (ProcessMessage() == 0)	// Windows���s��������҂K�v������
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		// �p�b�h�̓��͍X�V����
		input.Update();

		sceneController.Update(input);
		sceneController.Draw();

		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();	// 1/60�b�o�߂���܂ő҂�
		++m_frame;

		// FPS(Frame Per Second)60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}
}

void Application::Terminate()
{
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
}
