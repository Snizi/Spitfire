#include "pch.h"


void getDistance(uintptr_t entity, uintptr_t* localPlayer, uintptr_t vectorOrigin);

void shoot(uintptr_t clientModule, uintptr_t dwForceLeft);

bool checkTrigger(uintptr_t* localPlayer, uintptr_t m_iCrosshairId, uintptr_t clientModule, uintptr_t dwEntityList, uintptr_t m_iTeamNum, uintptr_t m_iHealth, uintptr_t vectorOrigin);

void handleTrigger(uintptr_t* localPlayer, uintptr_t m_iCrosshairId, uintptr_t clientModule, uintptr_t dwEntityList, uintptr_t m_iTeamNum, uintptr_t m_iHealth, uintptr_t vectorOrigin, uintptr_t dwForceLeft, int tbDelay);
