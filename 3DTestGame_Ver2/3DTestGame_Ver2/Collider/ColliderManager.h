#pragma once
#include "Vector3.h"

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();

	// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
	bool SphereToSphere(const Vector3& pos1, float radius1, const Vector3& pos2, float radius2);
};

