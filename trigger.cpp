#include "pch.h"


struct vector
{
	float x, y, z;
};

void getDistance(uintptr_t entity, uintptr_t* localPlayer, uintptr_t vectorOrigin)
{
	vector myLocation = *(vector*)(*localPlayer + vectorOrigin);
	vector enemyLocation = *(vector*)(entity + vectorOrigin);

}

void shoot(uintptr_t clientModule, uintptr_t dwForceLeft, int tbDelay)
{
	Sleep(tbDelay);
	*(int*)(clientModule + dwForceLeft) = 5;
	Sleep(20);
	*(int*)(clientModule + dwForceLeft) = 4;

}

bool checkTrigger(uintptr_t* localPlayer, uintptr_t m_iCrosshairId, uintptr_t clientModule, uintptr_t dwEntityList, uintptr_t m_iTeamNum, uintptr_t m_iHealth, uintptr_t vectorOrigin, int myTeam)
{
	int crosshair = *(int*)(*localPlayer + m_iCrosshairId);
	if (crosshair != 0 && crosshair < 64)
	{
		uintptr_t entity = clientModule + dwEntityList + ((crosshair - 1) * 0x10);
		int eTeam = *(int*)entity + m_iTeamNum;
		int eHealth = *(int*)entity + m_iHealth;
		if (eTeam != myTeam && eHealth > 0)
		{
			getDistance(entity, localPlayer, vectorOrigin);
			return true;

		}
		else
			return false;


	}
	else
		return false;


}
void handleTrigger(uintptr_t* localPlayer, uintptr_t m_iCrosshairId, uintptr_t clientModule, uintptr_t dwEntityList, uintptr_t m_iTeamNum, uintptr_t m_iHealth, uintptr_t vectorOrigin, uintptr_t dwForceLeft, int tbDelay)
{
	if (checkTrigger(localPlayer, m_iCrosshairId, clientModule, dwEntityList, m_iTeamNum, m_iHealth, vectorOrigin, m_iTeamNum))
	{

		shoot(clientModule, dwForceLeft, tbDelay);
	}
}