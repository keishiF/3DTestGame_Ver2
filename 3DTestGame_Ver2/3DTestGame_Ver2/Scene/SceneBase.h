#pragma once

class Input;
class SceneController;

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase(SceneController& controller);

	// �X�V�A�`��
	virtual void Update(Input& input) abstract;
	virtual void Draw() = 0;

protected:
	SceneController& m_controller;
};

