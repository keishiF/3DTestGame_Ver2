#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

bool ColliderManager::SphereToSphere(const Vec3& pos1, float radius1, const Vec3& pos2, float radius2)
{
	float distX = pos1.x - pos2.x;
	float distY = pos1.y - pos2.y;
	float distZ = pos1.z - pos2.z;
	float dist = (distX * distX) + (distY * distY) + (distZ * distZ);
	dist = sqrtf(dist);

	if (dist < (radius1 + radius2))
	{
		return true;
	}

	return false;
}
