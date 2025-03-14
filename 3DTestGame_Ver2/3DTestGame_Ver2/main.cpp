#include "DxLib.h"
#include "Application.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application& app = Application::GetInstance();

#ifdef _DEBUG
	AllocConsole();                                        // �R���\�[��
	FILE* out = 0; freopen_s(&out, "CON", "w", stdout); // stdout
	FILE* in = 0; freopen_s(&in, "CON", "r", stdin);   // stdin
#endif

	// �A�v���P�[�V�����̏�����
	if (!app.Init())
	{
		return -1;
	}

	// ���C�����[�v
	app.Run();

	// �㏈��
	app.Terminate();

	return 0;				// �\�t�g�̏I�� 
}