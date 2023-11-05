#pragma once
#include "Valve/Game.h"
#include "Valve/Bone.h"

namespace MenuConfig
{
	inline bool ShowMenu = false;
	inline std::string path = "";

	inline bool ShowBoneESP = false;
	inline bool ShowBoxESP = false;
	inline bool ShowHealthBar = false;
	inline bool ShowWeaponESP = false;
	inline bool ShowDistance = false;
	inline bool ShowEyeRay = false;
	inline bool ShowPlayerName = false;

	inline bool AimBot = false;
	inline int AimBotHotKey = 0;
	// 0: head 1: neck 3: spine
	inline int  AimPosition = 0;
	inline bool ShowAimFovRange = false;
	inline ImColor AimFovRangeColor = ImColor(230, 230, 230, 255);
	inline DWORD  AimPositionIndex = BONEINDEX::head;
	inline bool VisibleCheck = false;
	// 0: normal 1: dynamic
	inline int  BoxType = 0;
	// 0: Vertical 1: Horizontal
	inline int  HealthBarType = 0;

	inline ImColor BoneColor = ImColor(255, 255, 255, 255);
	inline ImColor BoxColor = ImColor(255, 255, 255, 255);
	inline ImColor EyeRayColor = ImColor(255, 0, 0, 255);

	inline bool TriggerBot = false;
	inline int TriggerHotKey = 0;
	inline int TriggerMode = 0;
	inline bool Pressed = false;// for toggle mode
	inline bool Shoot = false;// so that it doesn’t aim when the trigger hits

	inline bool TeamCheck = false;
	inline bool OBSBypass = false;
	inline bool BunnyHop = false;
	
	inline bool ShowHeadShootLine = false;
	inline ImColor HeadShootLineColor = ImColor(255, 255, 255, 255);

	inline bool ShowFovLine = false;
	inline ImColor FovLineColor = ImColor(55, 55, 55, 220);
	inline float FovLineSize = 60.f;

	inline bool ShowLineToEnemy = false;
	inline ImColor LineToEnemyColor = ImColor(255, 255, 255, 220);

	inline bool ShowWhenSpec = false;
}