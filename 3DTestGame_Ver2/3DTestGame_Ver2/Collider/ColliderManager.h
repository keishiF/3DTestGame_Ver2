#pragma once
#include "Vec3.h"

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	// ���Ƌ��̓����蔻��
	bool SphereToSphere(const Vec3& pos1, float radius1, const Vec3& pos2, float radius2);
};

