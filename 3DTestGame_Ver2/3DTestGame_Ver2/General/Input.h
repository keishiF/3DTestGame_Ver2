#pragma once
class Input
{
public:
	Input();

	void Update();

	bool IsPress(int button);

	bool IsTrigger(int button);

private:
	// 入力
	int m_padInput;

	int m_rsInput;

	// 前フレームの入力
	int m_lastInput;
};

