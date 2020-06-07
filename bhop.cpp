#include "pch.h"
#include "bhop.h"


void bhop(uintptr_t* localPlayer, uintptr_t m_fFlags, uintptr_t* forceFlag)
{

	BYTE flag = *(BYTE*)(*localPlayer + m_fFlags);


	if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0))
	{
		*forceFlag = 6;
	}
}
