#include "pch.h"





struct vector
{
	float x, y, z;
};

void getDistance(DWORD entity, uintptr_t* localPlayer, uintptr_t vectorOrigin)
{
	vector myLocation = *(vector*)(*localPlayer + vectorOrigin);
	vector enemyLocation = *(vector*)(entity + vectorOrigin);
}

void shoot(int tbDelay, uintptr_t clientModule, uintptr_t dwForceAttack)
{
	Sleep(tbDelay);
	*(int*)(clientModule + dwForceAttack) = 5;
	Sleep(20);
	*(int*)(clientModule + dwForceAttack) = 4;
}

bool checkTrigger(uintptr_t* localPlayer, uintptr_t m_iCrosshairId, uintptr_t clientModule, uintptr_t Enti)
{
	int crosshair = *(int*)(*localPlayer + m_iCrosshairId);
	if (crosshair != 0 && crosshair < 64)
	{
		DWORD entity = clientModule + 
	}

}
