#pragma once
#include "../Components/Valve/Game.h"
#include "../Components/Valve/Entity.h"
#include "../Components/MenuConfig.hpp"
#include <chrono>

namespace TriggerBot
{
	inline DWORD TriggerDelay = 90; // ms
	inline int HotKey = VK_LMENU;
	inline std::vector<int> HotKeyList{VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};
	inline int Mode = 0;

	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}
	inline void SetMode(int Index)
	{
		Mode = Index;
	}

	// Triggerbot
	void Run(const CEntity& LocalEntity);
}