#include "pch.h"
#include "bhop.h"


struct Vec3 {
	float x, y, z;

	Vec3 operator+(Vec3 d) {
		return { x + d.x, y + d.y, z + d.z };
	}
	Vec3 operator-(Vec3 d) {
		return { x - d.x, y - d.y, z - d.z };
	}
	Vec3 operator*(float d)
	{
		return { x * d, y * d, z * d };
	}

	void Normalize() {
		while (y < -180) {
			y += 360;
		}
		while (y > 180) {
			y -= 360;
		}
		if (x > 89) {
			x = 89;
		}
		if (x < -89) {
			x = -89;
		}
	}
};

bool RCS(uintptr_t engineModule, uintptr_t* localPlayer, bool bRCS, uintptr_t dwClientState, uintptr_t dwClientState_viewAngles, uintptr_t m_iShotsFired, uintptr_t m_aimPunchAngle, uintptr_t m_fFlags, uintptr_t* forceFlag)
{

	Vec3* viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_viewAngles);

	int* iShotsFired = (int*)(*localPlayer + m_iShotsFired);

	Vec3* aimPunchAngle = (Vec3*)(*localPlayer + m_aimPunchAngle);

	Vec3 oPunch{ 0, 0, 0 };

	while (bRCS) {

		bhop(localPlayer, m_fFlags, forceFlag);

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
			return false;



		Vec3 punchAngle = *aimPunchAngle * 2;
		if (*iShotsFired > 1)
		{
			Vec3 newAngle = *viewAngles + oPunch - punchAngle;

			newAngle.Normalize();

			*viewAngles = newAngle;

		}
		oPunch = punchAngle;

	}
}

