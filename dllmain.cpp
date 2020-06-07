// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "offsets.h"
#include "RCS.h"
#include "bhop.h"

struct vector
{
	float x, y, z;
};

void getDistance(DWORD entity, uintptr_t* localPlayer)
{
	vector myLocation = *(vector*)(*localPlayer + offsets::vectorOrigin);
	vector enemyLocation = *(vector*)(entity + offsets::vectorOrigin);;

}


void shoot(int tbDelay, uintptr_t clientModule)
{
	Sleep(tbDelay);
	*(int*)(clientModule + offsets::dwForceAttack) = 5;
	Sleep(20);
	*(int*)(clientModule + offsets::dwForceAttack) = 4;
}


bool checkTrigger(uintptr_t* localPlayer, uintptr_t clientModule, int myTeam)
{
	int crosshair = *(int*)(*localPlayer + offsets::m_iCrosshairId);
	if (crosshair != 0 && crosshair < 64)
	{
		DWORD entity = clientModule + offsets::dwEntityList + ((crosshair - 1) * 0x10);
		int eTeam = *(int*)entity + offsets::m_iTeamNum;
		int eHealth = *(int*)entity + offsets::m_iHealth;
		if (eTeam != myTeam && eHealth > 0)
		{
			getDistance(entity, localPlayer);
			return true;
		}

		else
			return false;
	}
	else
		return false;
}


void handleTrigger(uintptr_t* localPlayer, uintptr_t clientModule, int myTeam)
{
	if (checkTrigger(localPlayer, clientModule, myTeam))
		shoot(1, clientModule);
}


DWORD WINAPI main(HMODULE hModule) {

	uintptr_t clientModule = (uintptr_t)GetModuleHandle(L"client_panorama.dll");

	uintptr_t engineModule = (uintptr_t)GetModuleHandle(L"engine.dll");

	auto const localPlayer = (uintptr_t*)(clientModule + offsets::dwLocalPlayer);

	bool bRCS = false, bTrigger = false;


	uintptr_t* forceFlag = (uintptr_t*)(clientModule + offsets::dwForceJump);

	while (true) {

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
			bRCS = !bRCS;
		
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			int myTeam = *(int*)(*localPlayer + offsets::m_iTeamNum);
			bTrigger = !bTrigger;
		}
		if (*localPlayer) {

			bhop(localPlayer, offsets::m_fFlags, forceFlag);

			if (bRCS)
				bRCS = RCS(engineModule, localPlayer, bRCS, offsets::dwClientState, offsets::dwClientState_viewAngles, offsets::m_iShotsFired, offsets::m_aimPunchAngle, offsets::m_fFlags, forceFlag);

			if (bTrigger)
			{
				int myTeam = *(int*)(*localPlayer + offsets::m_iTeamNum);
				handleTrigger(localPlayer, clientModule, myTeam);
			}

		}
		Sleep(1);
	}
	

	 

	return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(main), hModule, NULL, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

