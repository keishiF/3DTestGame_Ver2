#pragma once
#include <cmath>

// 3�����x�N�g���N���X
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{

	}

	Vector3 operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3 operator+(const Vector3& vec) const
	{
		Vector3 temp{ x + vec.x, y + vec.y, z + vec.z };
		return temp;
	}

	Vector3 operator-=(const Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z += vec.z;
		return *this;
	}

	Vector3 operator-(const Vector3& vec) const
	{
		Vector3 temp{ x - vec.x, y - vec.y, z + vec.z };
		return temp;
	}

	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	Vector3 operator*(float scale) const
	{
		Vector3 temp{ x * scale, y * scale, z * scale };
		return temp;
	}

	Vector3 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	Vector3 operator/(float scale) const
	{
		Vector3 temp{ x / scale,y / scale, z / scale };
		return temp;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	// ���g�̒�����1�ɂ���(���K��)
	void Normalize()
	{
		float len = Length();
		if (len <= 0)
		{
			// �[���x�N�g���͂��̂܂�
			return;
		}
		x /= len;
		y /= len;
		z /= len;
	}

	// ���g�̒�����1�ɂ����x�N�g���̎擾
	// (���̊֐���ǂ�ł����g�̒����͕ω����Ȃ�)
	Vector3 GetNormalize() const
	{
		float len = Length();
		if (len <= 0.0f)
		{
			return *this;
		}
		return (*this) / len;
	}

	static Vector3 Lerp(Vector3 start, Vector3 end, float t)
	{
		Vector3 temp;
		temp.x = std::lerp(start.x, end.x, t);
		temp.y = std::lerp(start.y, end.y, t);
		temp.z = std::lerp(start.z, end.z, t);
		return temp;
	}
};