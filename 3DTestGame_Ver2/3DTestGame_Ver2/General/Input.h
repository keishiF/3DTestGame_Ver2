#pragma once
class Input
{
public:
	Input();

	void Update();

	bool IsPress(int button);

	bool IsTrigger(int button);

private:
	// “ü—Í
	int m_padInput;
	// ‘OƒtƒŒ[ƒ€‚Ì“ü—Í
	int m_lastInput;
};

