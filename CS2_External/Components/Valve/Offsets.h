#pragma once
#include <Windows.h>
#include "../ProcessManager.hpp"

//05.11.2023
namespace Offset
{
	//Updated to Latest: 9.11.2023
	inline DWORD EntityList = 0x17ADAF0;
	inline DWORD Matrix = 0x180C0F0;
	inline DWORD ViewAngle = 0x186B108;
	inline DWORD LocalPlayerController = 0x17FCDC8;
	inline DWORD LocalPlayerPawn = 0x16B9398;
	inline DWORD ForceJump = 0x16B2830;
	inline DWORD GlobalVars = 0x16AE4A8;

	struct //Updated to Latest: 9.11.2023
	{
		DWORD Health = 0x32C; //C_BaseEntity - m_iHealth
		DWORD TeamID = 0x3BF; //C_BaseEntity - m_iTeamNum
		DWORD IsAlive = 0x7C4; //CCSPlayerController - m_bPawnIsAlive
		DWORD PlayerPawn = 0x7BC; //CCSPlayerController - m_hPlayerPawn
		DWORD iszPlayerName = 0x610; //CBasePlayerController - m_iszPlayerName
	}Entity;

	struct //Updated to Latest: 9.11.2023
	{
		DWORD Pos = 0x1224; //its new but i cant find location!
		DWORD MaxHealth = 0x328; //C_BaseEntity - m_iMaxHealth
		DWORD CurrentHealth = 0x32C; //C_BaseEntity - m_iHealth
		DWORD GameSceneNode = 0x310; //C_BaseEntity - m_pGameSceneNode
		DWORD BoneArray = 0x1E0; //its new but i cant find location!
		DWORD angEyeAngles = 0x1510; //C_CSPlayerPawnBase - m_angEyeAngles
		DWORD vecLastClipCameraPos = 0x128C; //C_CSPlayerPawnBase - m_vecLastClipCameraPos
		DWORD pClippingWeapon = 0x12A8; //C_CSPlayerPawnBase - m_pClippingWeapon
		DWORD iShotsFired = 0x1418; //C_CSPlayerPawnBase - m_iShotsFired
		DWORD aimPunchAngle = 0x1714; //C_CSPlayerPawn - m_aimPunchAngle
		DWORD aimPunchCache = 0x1738; //C_CSPlayerPawn - m_aimPunchCache
		DWORD iIDEntIndex = 0x153C; //C_CSPlayerPawnBase - m_iIDEntIndex
		DWORD iTeamNum = 0x3BF; //C_BaseEntity - m_iTeamNum
		DWORD CameraServices = 0x10E0; //C_BasePlayerPawn - m_pCameraServices
		DWORD iFov = 0x210; //CCSPlayerBase_CameraServices - m_iFOV
		DWORD iFovStart = 0x214; //CCSPlayerBase_CameraServices - m_iFOVStart
		DWORD fFlags = 0x3C8; //C_BaseEntity - m_fFlags
		DWORD bSpottedByMask = 0x1630 + 0xC; //C_CSPlayerPawnBase + EntitySpottedState_t  -  m_entitySpottedState + m_bSpottedByMask
	}Pawn;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	namespace Signatures
	{
		const std::string GlobalVars = "48 89 0D ?? ?? ?? ?? 48 89 41";
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string ForceJump = "48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45";
	}

	bool UpdateOffsets();
}
