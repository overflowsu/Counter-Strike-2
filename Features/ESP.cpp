#include "ESP.h"
#include "../Offsets/offsets.h"
#include "../Offsets/client.h"
#include "../Helpers/render.h"
#include "../Helpers/vector.h"
#include "../Helpers/vars.h"

using namespace cs2_dumper::offsets::client_dll;
using namespace cs2_dumper::schemas::client_dll;

void RunEsp(uintptr_t client, bool enable, bool box, bool name) {
	if (enable) {
		uintptr_t lpp;
		ProcessMgr.ReadMemory(client + dwLocalPlayerPawn, lpp);
		int lpt;
		ProcessMgr.ReadMemory(lpp + C_BaseEntity::m_iTeamNum, lpt);
		Vector3 lpo;
		ProcessMgr.ReadMemory(lpp + C_BasePlayerPawn::m_vOldOrigin, lpo);
		view_matrix_t vm;
		ProcessMgr.ReadMemory(client + dwViewMatrix, vm);
		uintptr_t ent;
		ProcessMgr.ReadMemory(client + dwEntityList, ent);
		for (int index = 1; index < 32; ++index) {
			uintptr_t el;
			ProcessMgr.ReadMemory(ent + (8 * (index & 0x7FFF) >> 9) + 16, el);
			if (!el) continue;
			uintptr_t pl;
			ProcessMgr.ReadMemory(el + 120 * (index & 0x1FF), pl);
			if (!pl) continue;
			int pt;
			ProcessMgr.ReadMemory(pl + C_BaseEntity::m_iTeamNum, pt);
			if (pt == lpt) continue;
			char pn[MAX_PATH]{};
			ProcessMgr.ReadMemory(pl + CBasePlayerController::m_iszPlayerName, pn);
			uint32_t pp;
			ProcessMgr.ReadMemory(pl + CCSPlayerController::m_hPlayerPawn, pp);
			uintptr_t el2;
			ProcessMgr.ReadMemory(ent + 0x8 * ((pp & 0x7FFF) >> 9) + 16, el2);
			if (!el2) continue;
			uintptr_t cspp;
			ProcessMgr.ReadMemory(el2 + 120 * (pp & 0x1FF), cspp);
			if (!cspp) continue;
			int ph;
			ProcessMgr.ReadMemory(cspp + C_BaseEntity::m_iHealth, ph);
			if (ph <= 0 || ph > 100) continue;
			if (cspp == lpp) continue;
			Vector3 origin;
			ProcessMgr.ReadMemory(cspp + C_BasePlayerPawn::m_vOldOrigin, origin);
			Vector3 head = { origin.x, origin.y, origin.z + 75.f };
			Vector3 origin_w2s = origin.w2s(vm);
			Vector3 head_w2s = head.w2s(vm);
			float height = origin_w2s.y - head_w2s.y;
			float width = height / 2.4f;
			RGB enemy = { 255, 0, 0 };
			if (name) Render::DrawLabel(head_w2s.x - width / 2 - 5, head_w2s.y - 15, { 255, 255, 255 }, pn);
			if (box) Render::DrawRect(head_w2s.x - width / 2, head_w2s.y, width, height, enemy, 2);
		}
	}
}

// ESP Core Features by TxmuXn