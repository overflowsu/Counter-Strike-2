#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"
#include "../Globals.hpp"

struct C_UTL_VECTOR
{
	DWORD64 Count = 0;
	DWORD64 Data = 0;
};

class PlayerController
{
public:
	DWORD64 Address = 0;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	DWORD Pawn = 0;
	std::string PlayerName;
public:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	bool GetPlayerName();
	DWORD64 GetPlayerPawnAddress();
};

class PlayerPawn
{
public:
	enum class Flags
	{
		NONE,
		IN_AIR = 1 << 0
	};

	DWORD64 Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
	std::string WeaponName;
	DWORD ShotsFired;
	Vec2 AimPunchAngle;
	C_UTL_VECTOR AimPunchCache;
	int Health;
	int TeamID;
	int Fov;
	DWORD64 bSpottedByMask;
	int fFlags;
public:
	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
	bool GetWeaponName();
	bool GetShotsFired();
	bool GetAimPunchAngle();
	bool GetHealth();
	bool GetTeamID();
	bool GetFov();
	bool GetSpotted();
	bool GetFFlags();
	bool GetAimPunchCache();

	constexpr bool HasFlag(const Flags Flag) const noexcept {
		return fFlags & (int)Flag;
	}
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
public:
	// 更新数据
	bool UpdateController(const DWORD64& PlayerControllerAddress);
	bool UpdatePawn(const DWORD64& PlayerPawnAddress);
	// 是否存活
	bool IsAlive();
	// 是否在屏幕内
	bool IsInScreen();
	// 获取骨骼数据
	CBone GetBone() const;
};