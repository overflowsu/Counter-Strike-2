#pragma once
#include "../Helpers/memory.h"
#include "../Offsets/offsets.h"
#include "../Offsets/client.h"
#include "../Helpers/render.h"
#include "../Helpers/vector.h"
#include "../Helpers/vars.h"

using namespace cs2_dumper::offsets::client_dll;
using namespace cs2_dumper::schemas::client_dll;

void RunFovChanger(uintptr_t client, bool enable, int fov) {
	if (enable) {
		uint16_t desired = (uint16_t)fov;
		uintptr_t lpp;
		ProcessMgr.ReadMemory(client + dwLocalPlayerPawn, lpp);
		uintptr_t cs;
		ProcessMgr.ReadMemory(lpp + C_BasePlayerPawn::m_pCameraServices, cs);
		ProcessMgr.WriteMemory(cs + CCSPlayerBase_CameraServices::m_iFOV, desired);
	}
}

// Fov Changer by TxmuXn