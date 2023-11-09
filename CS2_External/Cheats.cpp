#define IMGUI_DEFINE_MATH_OPERATORS
#include <stdexcept>
#include <d3d9.h>
#include <tchar.h>
#include "Components/ByteArray.h"
#include "Components/NavElements.h"
#include "Components/EtcElements.h"
#include "Cheats.h"
#include "Components/Valve/Render.hpp"
#include "Components/ConfigMenu.hpp"
#include "Components/MenuConfig.hpp"
#include "Components/ConfigSaver.hpp"
#include "Features/Watermark.hpp"

ImFont* medium;
ImFont* bold;
ImFont* tab_icons;
ImFont* logo;
ImFont* tab_title;
ImFont* tab_title_icon;
ImFont* subtab_title;
ImFont* combo_arrow;

enum heads {
	aimbot, trigger, visuals, misc, config
};

enum sub_heads {
	general, _general, _general_, __general__, esp, colors, glow, camera
};

void Cheats::InitFont() 
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	medium = io.Fonts->AddFontFromMemoryTTF(PTRootUIMedium, sizeof(PTRootUIMedium), 15.0f, &font_config, ranges);
	bold = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	tab_icons = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 15.0f, &font_config, ranges);
	logo = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 21.0f, &font_config, ranges);

	tab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 19.0f, &font_config, ranges);
	tab_title_icon = io.Fonts->AddFontFromMemoryTTF(clarityfont, sizeof(clarityfont), 18.0f, &font_config, ranges);

	subtab_title = io.Fonts->AddFontFromMemoryTTF(PTRootUIBold, sizeof(PTRootUIBold), 15.0f, &font_config, ranges);

	combo_arrow = io.Fonts->AddFontFromMemoryTTF(combo, sizeof(combo), 9.0f, &font_config, ranges);

	// Our state
	ImVec4 clear_color = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
}

void Cheats::Menu()
{
	static heads tab{ aimbot };
	static sub_heads subtab{ general };

	const char* tab_name = tab == aimbot ? "Aimbot" : tab == trigger ? "Trigger" : tab == visuals ? "Visuals" : tab == misc ? "Misc" : tab == config ? "Configs" : 0;
	const char* tab_icon = tab == aimbot ? "B" : tab == trigger ? "C" : tab == visuals ? "D" : tab == misc ? "E" : tab == config ? "G" : 0;

	static bool boolean, boolean_1 = false;
	static int sliderscalar, combo = 0;

	const char* combo_items[3] = { "Value", "Value 1", "Value 2" };

	ImGui::SetNextWindowSize({ 730, 460 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

	if (ImGui::Begin("OVERFLOW", nullptr, ImGuiWindowFlags_NoDecoration))
	{
		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();
		ImGuiStyle style = ImGui::GetStyle();

		auto draw = ImGui::GetWindowDrawList();
		draw->AddRectFilled(pos, ImVec2(pos.x + 210, pos.y + size.y), ImColor(24, 24, 26), style.WindowRounding, ImDrawFlags_RoundCornersLeft);
		draw->AddLine(ImVec2(pos.x + 210, pos.y + 2), ImVec2(pos.x + 210, pos.y + size.y - 2), ImColor(0,255,255));
		draw->AddLine(ImVec2(pos.x + 47, pos.y + 2), ImVec2(pos.x + 47, pos.y + size.y - 2), ImColor(0, 255, 255));
		draw->AddLine(ImVec2(pos.x + 2, pos.y + 47), ImVec2(pos.x + 47, pos.y + 47), ImColor(1.0f, 1.0f, 1.0f, 0.03f));
		draw->AddLine(ImVec2(pos.x + 63, pos.y + 47), ImVec2(pos.x + 195, pos.y + 47), ImColor(0, 255, 255));
		draw->AddText(logo, 25.0f, ImVec2(pos.x + 12, pos.y + 12), ImColor(0, 255, 255), "OF");
		draw->AddText(tab_title, 19.0f, ImVec2(pos.x + 93, pos.y + 15), ImColor(0, 255, 255), tab_name);
		draw->AddRect(pos + ImVec2(1, 1), pos + size - ImVec2(1, 1), ImColor(0, 255, 255), style.WindowRounding);

		ImGui::SetCursorPos({ 8, 56 });
		ImGui::BeginGroup(); {
			if (elements::tab("B", tab == aimbot)) { tab = aimbot; }
			if (elements::tab("C", tab == trigger)) { tab = trigger; }
			if (elements::tab("D", tab == visuals)) { tab = visuals; }
			if (elements::tab("E", tab == misc)) { tab = misc; }
			if (elements::tab("G", tab == config)) { tab = config; }
		} ImGui::EndGroup();

		switch (tab) {
		case aimbot:
			ImGui::SetCursorPos({ 57, 55 });
			ImGui::BeginGroup(); {
				if (elements::subtab("General", subtab == general)) { subtab = general; }
			} ImGui::EndGroup();

			switch (subtab) {
			case general:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 130)); {
					ImGui::Checkbox("Enable", &MenuConfig::AimBot);
					ImGui::SameLine();
					ImGui::PushItemWidth(83.0f);
					if (ImGui::Combo("Hotkey", &MenuConfig::AimBotHotKey, "LBUTTON\0MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
					{
						AimControl::SetHotKey(MenuConfig::AimBotHotKey);
					}
					ImGui::PopItemWidth();
					if (ImGui::Combo("Hitbox", &MenuConfig::AimPosition, "Head\0Neck\0Spine"))
					{
						switch (MenuConfig::AimPosition)
						{
							case 0:
								MenuConfig::AimPositionIndex = BONEINDEX::head;
								break;
							case 1:
								MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
								break;
							case 2:
								MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
								break;
							default:
								break;
						}
					}	
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 16 });
				e_elements::begin_child("Features", ImVec2(240, 160)); {
					ImGui::Checkbox("Show Fov", &MenuConfig::ShowAimFovRange);
					ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&MenuConfig::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Circle Color");
					ImGui::Checkbox("Visible Check", &MenuConfig::VisibleCheck);
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 226, 160 });
				e_elements::begin_child("Settings", ImVec2(240, 120)); {
					float FovMin = 0.1f, FovMax = 89.f;
					float SmoothMin = 0.f, SmoothMax = 0.9f;
					Gui.SliderScalarEx1("Fov", ImGuiDataType_Float, &AimControl::AimFov, &FovMin, &FovMax, "%.1f", ImGuiSliderFlags_None);
					Gui.SliderScalarEx1("Smooth", ImGuiDataType_Float, &AimControl::Smooth, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 190 });
				e_elements::begin_child("Recoil Control", ImVec2(240, 150)); {
					int BulletMin = 1, BulletMax = 6;
					float RecoilMin = 0.f, RecoilMax = 2.f;
					Gui.SliderScalarEx1("Start", ImGuiDataType_U32, &AimControl::RCSBullet, &BulletMin, &BulletMax, "%d", ImGuiSliderFlags_None);
					Gui.SliderScalarEx1("Yaw", ImGuiDataType_Float, &AimControl::RCSScale.x, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
					Gui.SliderScalarEx1("Pitch", ImGuiDataType_Float, &AimControl::RCSScale.y, &RecoilMin, &RecoilMax, "%.1f", ImGuiSliderFlags_None);
				}
				e_elements::end_child();
				break;
			}
			break;
		
		case trigger:
			ImGui::SetCursorPos({ 57, 55 });
			ImGui::BeginGroup(); {
				if (elements::subtab("General", subtab == _general)) { subtab = _general; }
			} ImGui::EndGroup();

			switch (subtab) {
			case _general:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 130)); {
					ImGui::Checkbox("Enable", &MenuConfig::TriggerBot);
					ImGui::SameLine();
					ImGui::PushItemWidth(83.0f);
					if (ImGui::Combo("Hotkey", &MenuConfig::TriggerHotKey, "MENU\0RBUTTON\0XBUTTON1\0XBUTTON2\0CAPITAL\0SHIFT\0CONTROL"))
					{
						TriggerBot::SetHotKey(MenuConfig::TriggerHotKey);
					}
					ImGui::PopItemWidth();
					if (ImGui::Combo("Mode", &MenuConfig::TriggerMode, "Hold\0Toggle"))
					{
						TriggerBot::SetMode(MenuConfig::TriggerMode);
					}
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 16 });
				e_elements::begin_child("Settings", ImVec2(240, 100)); {
					DWORD TriggerDelayMin = 15, TriggerDelayMax = 170;
					Gui.SliderScalarEx1("Delay", ImGuiDataType_U32, &TriggerBot::TriggerDelay, &TriggerDelayMin, &TriggerDelayMax, "%d", ImGuiSliderFlags_None);
				}
				e_elements::end_child();

				break;
			}
			break;

		case visuals:
			ImGui::SetCursorPos({ 57, 55 });
			ImGui::BeginGroup(); {
				if (elements::subtab("ESP", subtab == esp)) { subtab = esp; }
				if (elements::subtab("Colors", subtab == colors)) { subtab = colors; }
			} ImGui::EndGroup();

			switch (subtab) {
			case esp:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 423)); {
					ImGui::Checkbox("Box", &MenuConfig::ShowBoxESP);
					ImGui::Checkbox("Bone", &MenuConfig::ShowBoneESP);
					ImGui::Checkbox("Eye Ray", &MenuConfig::ShowEyeRay);
					ImGui::Checkbox("Health Bar", &MenuConfig::ShowHealthBar);
					ImGui::Checkbox("Weapon", &MenuConfig::ShowWeaponESP);
					ImGui::Checkbox("Distance", &MenuConfig::ShowDistance);
					ImGui::Checkbox("Player", &MenuConfig::ShowPlayerName);
					ImGui::Checkbox("Headshot Line", &MenuConfig::ShowHeadShootLine);
					ImGui::Checkbox("Line To Enemy", &MenuConfig::ShowLineToEnemy);
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 16 });
				e_elements::begin_child("Preview", ImVec2(240, 290)); {
					ImVec2 windowSize = ImGui::GetWindowSize();
					ImVec2 rectSize(100, 150);
					ImVec2 rectPos((windowSize.x - rectSize.x) * 0.45f, (windowSize.y - rectSize.y) * 0.3f);
					ImVec2 centerPos = ImGui::GetCursorScreenPos();
					centerPos.x += rectPos.x;
					centerPos.y += rectPos.y;
						if (MenuConfig::ShowBoxESP) {
							ImU32 boxColor = MenuConfig::BoxColor;
							ImVec2 rectStartPos = centerPos;
							ImVec2 rectEndPos(rectStartPos.x + rectSize.x, rectStartPos.y + rectSize.y);
							ImGui::GetWindowDrawList()->AddRect(rectStartPos, rectEndPos, IM_COL32(0, 0, 0, 255), 0.0f, ImDrawCornerFlags_All, 2.0f);//outline
							ImGui::GetWindowDrawList()->AddRect(rectStartPos, rectEndPos, boxColor, 0.0f, ImDrawCornerFlags_All, 1.0f); // mainrec
						}

						if (MenuConfig::ShowEyeRay) {
							ImU32 EyeC = MenuConfig::EyeRayColor;
							ImVec2 lineStart(centerPos.x + 50, centerPos.y + 15);
							ImVec2 lineEnd(centerPos.x + 95, centerPos.y + 15);
							ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, EyeC, 2.0f);

						}
						if (MenuConfig::ShowBoneESP) {
							ImU32 boneColor = MenuConfig::BoneColor;
							ImVec2 lineStart(centerPos.x + 50, centerPos.y + 15);
							ImVec2 lineEnd(centerPos.x + 50, centerPos.y + 110);
							ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, boneColor, 2.0f);
							ImVec2 Rarm(centerPos.x + 50, centerPos.y + 30);
							ImVec2 Rarme(centerPos.x + 30, centerPos.y + 60);
							ImGui::GetWindowDrawList()->AddLine(Rarm, Rarme, boneColor, 2.0f);
							ImVec2 Larm(centerPos.x + 50, centerPos.y + 30);
							ImVec2 Larme(centerPos.x + 70, centerPos.y + 60);
							ImGui::GetWindowDrawList()->AddLine(Larm, Larme, boneColor, 2.0f);
							ImVec2 Rleg(centerPos.x + 50, centerPos.y + 110);
							ImVec2 Rlege(centerPos.x + 30, centerPos.y + 140);
							ImGui::GetWindowDrawList()->AddLine(Rleg, Rlege, boneColor, 2.0f);
							ImVec2 Lleg(centerPos.x + 50, centerPos.y + 110);
							ImVec2 Llege(centerPos.x + 70, centerPos.y + 140);
							ImGui::GetWindowDrawList()->AddLine(Lleg, Llege, boneColor, 2.0f);
						}

						//Healthbar
						if (MenuConfig::ShowHealthBar) {
							ImU32 greenColor = IM_COL32(0, 255, 0, 255);
							if (MenuConfig::HealthBarType == 0) {
								ImVec2 HBS(centerPos.x - 8, centerPos.y);
								ImVec2 HBE(centerPos.x - 3, centerPos.y + rectSize.y);
								ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, greenColor, 0.0f, ImDrawCornerFlags_All);
							}
							if (MenuConfig::HealthBarType == 1) {
								ImVec2 HBS(centerPos.x, centerPos.y - 6);
								ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y - 3);
								ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, greenColor, 0.0f, ImDrawCornerFlags_All);
							}
							if (MenuConfig::HealthBarType == 2) {
								ImVec2 HBS(centerPos.x, centerPos.y + rectSize.y + 6);
								ImVec2 HBE(centerPos.x + rectSize.x, centerPos.y + rectSize.y + 3);
								ImGui::GetWindowDrawList()->AddRectFilled(HBS, HBE, greenColor, 0.0f, ImDrawCornerFlags_All);
							}

						}

						//name text
						if (MenuConfig::ShowPlayerName) {
							if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 2) {
								ImVec2 textPos(centerPos.x + 18, centerPos.y - 18);
								ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "PlayerName");
							}
							if (MenuConfig::HealthBarType == 1) {
								ImVec2 textPos(centerPos.x + 18, centerPos.y - 22);
								ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "PlayerName");
							}
						}
						//distance text
						if (MenuConfig::ShowDistance) {
							ImVec2 textPos(centerPos.x + 105, centerPos.y);
							ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "20m");
						}

						//weapon text
						if (MenuConfig::ShowWeaponESP) {
							if (MenuConfig::HealthBarType == 2) {
								ImVec2 textPos(centerPos.x + 29, centerPos.y + 155);
								ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
							}
							if (MenuConfig::HealthBarType == 0 || MenuConfig::HealthBarType == 1) {
								ImVec2 textPos(centerPos.x + 29, centerPos.y + 150);
								ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), "Weapon");
							}
						}
					}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 320 });
				e_elements::begin_child("Settings", ImVec2(240, 120)); {
					ImGui::PushItemWidth(83.0f);
					ImGui::Combo("Box Type", &MenuConfig::BoxType, "Normal\0Dynamic");
					ImGui::Combo("Healthbar Type", &MenuConfig::HealthBarType, "Vetical\0Horizontal");
					ImGui::PopItemWidth();
				}
				e_elements::end_child();
				break;

			case colors:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("ESP Colors", ImVec2(240, 210)); {
					ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Box");

					ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Bone");

					ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Eye Ray");

					ImGui::ColorEdit4("##HeadShootLineColor", reinterpret_cast<float*>(&MenuConfig::HeadShootLineColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Headshot Line");

					ImGui::ColorEdit4("##LineToEnemyColor", reinterpret_cast<float*>(&MenuConfig::LineToEnemyColor), ImGuiColorEditFlags_NoInputs);
					ImGui::SameLine();
					ImGui::Text("Line to Enemy");
				}
				e_elements::end_child();
				break;
			}
			break;

		case misc:
			ImGui::SetCursorPos({ 57, 55 });
			ImGui::BeginGroup(); {
				if (elements::subtab("General", subtab == _general_)) { subtab = _general_; }
			} ImGui::EndGroup();

			switch (subtab) {
			case _general_:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 150)); {
					ImGui::Checkbox("Team Check", &MenuConfig::TeamCheck);
					ImGui::Checkbox("OBS Bypass", &MenuConfig::OBSBypass);
					ImGui::Checkbox("Work in Spectator", &MenuConfig::ShowWhenSpec);
					ImGui::Checkbox("WaterMark", &MenuConfig::WaterMark);
					ImGui::SameLine();
					if (ImGui::Button("..."))
						ImGui::OpenPopup("##...");
					if (ImGui::BeginPopup("##..."))
					{
						ImGui::TextUnformatted("Settings");
						ImGui::Checkbox("Cheat Name", &MenuConfig::watermarkcheat);
						ImGui::Checkbox("Fps", &MenuConfig::watermarkfps);
						ImGui::Checkbox("Time", &MenuConfig::watermarktime);
						ImGui::Checkbox("Username", &MenuConfig::watermarkuser);
						ImGui::EndPopup();
					}
				}
				e_elements::end_child();

				ImGui::SetCursorPos({ 476, 16 });
				e_elements::begin_child("Movement", ImVec2(240, 100)); {
					ImGui::Checkbox("BunnyHop(VAC)", &MenuConfig::BunnyHop);
				}
				e_elements::end_child();
				break;
			}
			break;

		case config:
			ImGui::SetCursorPos({ 57, 55 });
			ImGui::BeginGroup(); {
				if (elements::subtab("General", subtab == __general__)) { subtab = __general__; }
			} ImGui::EndGroup();

			switch (subtab) {
			case __general__:
				ImGui::SetCursorPos({ 226, 16 });
				e_elements::begin_child("General", ImVec2(240, 400)); {
					ConfigMenu::RenderConfigMenu();
				}
				e_elements::end_child();
				break;
			}
			break;
		}

		ImGui::End();
	}
}

void Cheats::Run()
{
	// EXTERNAL FEATURES
	Watermark::Render();

	// Show menu
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_HOME)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		// Check key state per 150ms once to avoid loop.
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		LastTimePoint = CurTimePoint;
	}

	if (MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	static int LocalPlayerControllerIndex = 1;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress) && !MenuConfig::ShowWhenSpec)
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;

		if (EntityAddress == LocalEntity.Controller.Address)
		{
			LocalPlayerControllerIndex = i;
			continue;
		}

		if (!Entity.UpdateController(EntityAddress))
			continue;

		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (MenuConfig::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		if (!Entity.IsAlive())
			continue;

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });


		if (DistanceToSight < MaxAimDistance)
		{
			MaxAimDistance = DistanceToSight;
			// From: https://github.com/redbg/CS2-Internal/blob/fc8e64430176a62f8800b7467884806708a865bb/src/include/Cheats.hpp#L129
			if (!MenuConfig::VisibleCheck ||
				Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) ||
				LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))
			{
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		// Draw Bone
		if (MenuConfig::ShowBoneESP)
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);

		// Draw eyeRay
		if (MenuConfig::ShowEyeRay)
			Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);

		// Box
		ImVec4 Rect;
		switch (MenuConfig::BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		default:
			break;
		}

		// Line to enemy
		if (MenuConfig::ShowLineToEnemy)
			Render::LineToEnemy(Rect, MenuConfig::LineToEnemyColor, 1.2);

		// Draw Box
		if (MenuConfig::ShowBoxESP)
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3);

		// Draw HealthBar
		if (MenuConfig::ShowHealthBar)
		{
			ImVec2 HealthBarPos, HealthBarSize;
			if (MenuConfig::HealthBarType == 0)
			{
				// Vertical
				HealthBarPos = { Rect.x - 7.f,Rect.y };
				HealthBarSize = { 7 ,Rect.w };
			}
			else
			{
				// Horizontal
				HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
				HealthBarSize = { 70,8 };
			}
			Render::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
		}

		// Draw weaponName
		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14);

		if (MenuConfig::ShowDistance)
			Render::DrawDistance(LocalEntity, Entity, Rect);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
		}

	}

	// Fov line
	if (MenuConfig::ShowFovLine)
		Render::DrawFov(LocalEntity, MenuConfig::FovLineSize, MenuConfig::FovLineColor, 1);

	// TriggerBot
	if (MenuConfig::TriggerMode == 1 && MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey) && MenuConfig::Pressed&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		MenuConfig::Pressed = false;
		LastTimePoint = CurTimePoint;
	}
	else if (MenuConfig::TriggerMode == 1 && MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey)&& !MenuConfig::Pressed&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		MenuConfig::Pressed = true;
		LastTimePoint = CurTimePoint;
	}

	if (MenuConfig::TriggerMode == 0 && MenuConfig::TriggerBot && GetAsyncKeyState(TriggerBot::HotKey))
	{
		MenuConfig::Shoot = true;
		TriggerBot::Run(LocalEntity);
		MenuConfig::Shoot = false;
	}
	else if (MenuConfig::TriggerMode == 1 && MenuConfig::TriggerBot && MenuConfig::Pressed) 
	{
		MenuConfig::Shoot = true;
		TriggerBot::Run(LocalEntity);
		MenuConfig::Shoot = false;
	}
			


	// HeadShoot Line
	if(MenuConfig::ShowHeadShootLine)
		Render::HeadShootLine(LocalEntity, MenuConfig::HeadShootLineColor);

	// Fov circle
	if(MenuConfig::ShowAimFovRange)
		Render::DrawFovCircle(LocalEntity);
	
	if (MenuConfig::BunnyHop)
		Bunnyhop::Run(LocalEntity);

	if (MenuConfig::AimBot && GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}