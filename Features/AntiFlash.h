#pragma once
#include "../Helpers/memory.h"
#include "../Offsets/offsets.h"
#include "../Offsets/client.h"

using namespace cs2_dumper::offsets::client_dll;
using namespace cs2_dumper::schemas::client_dll;

void RunAntiFlash(uintptr_t client, bool enable) {
	if (enable) {
		uintptr_t lpp;
		ProcessMgr.ReadMemory(client + dwLocalPlayerPawn, lpp);
		float duration{};
		ProcessMgr.WriteMemory(lpp + C_CSPlayerPawnBase::m_flFlashDuration, duration);
	}
}